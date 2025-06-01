#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#ifdef _WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif

class Server {
    int serverSocket;
    std::vector<std::thread> threads;
    std::vector<int> clients;
    std::mutex clientMutex;
    std::atomic<bool> running;
    sockaddr_in serverAddr;

public:
    Server(int port);
    void run();
    void acceptClients();
    void broadcastMessage(const std::string& message, int senderSocket);
    ~Server();
};

#endif