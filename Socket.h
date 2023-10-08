#ifndef WEBSERVER_SOCKET_H
#define WEBSERVER_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include "logger.h"

#define BUFFER_SIZE 4096

class Socket {
private:
    int socketFileDescriptor;
    struct sockaddr_in serverAddress;
    Logger* logger;

    Socket& createSocketFileDescriptor(int domain = AF_INET, int socketType = SOCK_STREAM, int protocol = 0);
public:
    explicit Socket(int domain = AF_INET, int socketType = SOCK_STREAM, int protocol = 0,
           in_addr_t internetAddress = INADDR_ANY, int portNumber = 8080);
    Socket& bindSocket();
    Socket& listenForConnections(int maxConnectionsNumber);
    Socket& handleConnections();
    static void* handleClient(void* arg);
};

#endif //WEBSERVER_SOCKET_H
