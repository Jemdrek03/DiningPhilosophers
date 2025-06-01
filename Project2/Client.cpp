#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#define close closesocket
#else
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

#include "Client.h"
#include <iostream>
#include <string>
#include <thread>

void runClient(const std::string& host, int port) {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }
#endif

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &serverAddr.sin_addr);

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to connect to server." << std::endl;
        return;
    }

    std::thread receiveThread([sock]() {
        char buffer[1024];
        while (true) {
            ssize_t bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
            if (bytes <= 0) break;
            buffer[bytes] = '\0';
            std::cout << "[CHAT] " << buffer << std::endl;
        }
    });

    std::string message;
    while (true) {
        std::getline(std::cin, message);
        if (message == "/exit") break;
        send(sock, message.c_str(), message.length(), 0);
    }

    close(sock);
    receiveThread.join();

#ifdef _WIN32
    WSACleanup();
#endif
}