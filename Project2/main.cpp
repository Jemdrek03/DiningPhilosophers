#ifdef _WIN32
#include <winsock2.h> // Windows socket header
#include <ws2tcpip.h> // Additional Windows socket utilities
#pragma comment(lib, "Ws2_32.lib") // Link with Ws2_32.lib
#define close closesocket // Replace close() with closesocket() on Windows
#else
#include <unistd.h> // POSIX API for close()
#include <netinet/in.h> // sockaddr_in and related structures
#include <arpa/inet.h> // inet_pton for IP conversion
#include <sys/socket.h> // Socket API
#endif

#include "Server.h"
#include <thread>
#include <iostream>
#include <string>
#include "Client.h"

int main(int argc, char* argv[]) {
    // If "client" argument is provided, run client logic
    if (argc > 1 && std::string(argv[1]) == "client") {
        runClient("127.0.0.1", 12345);
    } else {
        Server server(12345); // Start server on port 12345
        server.run(); // Run the server
    }
    return 0;
}
