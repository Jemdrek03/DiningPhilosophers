#include "ClientHandler.h"
#include "Server.h"
#include <cstring>
#include <iostream>
#ifdef _WIN32
#include <winsock2.h>
#define close closesocket
#else
#include <unistd.h>
#endif

void handleClient(int clientSocket, Server* server) {
    char buffer[1024];
    while (true) {
        ssize_t bytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';
        std::string msg = "Client " + std::to_string(clientSocket) + ": " + buffer;
        std::cout << msg << std::endl;
        server->broadcastMessage(msg, clientSocket);
    }
    std::cout << "Client " << clientSocket << " disconnected." << std::endl;
    close(clientSocket);
}