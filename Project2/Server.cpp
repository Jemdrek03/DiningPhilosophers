#include "Server.h"
#include <iostream>
#include <cstring>
#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#define close closesocket
#else
#include <unistd.h>
#include <sys/socket.h>
#endif

void handleClient(int clientSocket, Server* server);

Server::Server(int port) : running(true) {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);
#endif
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);
}

void Server::run() {
    std::thread(&Server::acceptClients, this).detach();
    while (running.load()) {
    }
}

void Server::acceptClients() {
    while (running.load()) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        {
            std::lock_guard<std::mutex> lock(clientMutex);
            clients.push_back(clientSocket);
        }
        threads.emplace_back(handleClient, clientSocket, this);
    }
}

void Server::broadcastMessage(const std::string& message, int senderSocket) {
    std::lock_guard<std::mutex> lock(clientMutex);
    for (int client : clients) {
        if (client != senderSocket) {
            send(client, message.c_str(), message.length(), 0);
        }
    }
}

Server::~Server() {
    running.store(false);
    for (auto& t : threads) if (t.joinable()) t.join();
    close(serverSocket);
#ifdef _WIN32
    WSACleanup();
#endif
}