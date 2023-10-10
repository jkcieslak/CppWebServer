#include "Socket.h"
#include "Matcher.h"
#include "Controller.h"
#include <iostream>
#include <exception>
#include <arpa/inet.h>
#include <regex.h>
#include <cstring>
#include <unistd.h>
#include <thread>
#include <sstream>

Socket::Socket(int domain, int socketType, int protocol, in_addr_t internetAddress, int portNumber) {
    this->logger = new Logger(std::cout, DEBUG);
    this->serverAddress.sin_family = domain;
    this->serverAddress.sin_addr.s_addr = internetAddress;
    this->serverAddress.sin_port = htons(portNumber);
    try {
        this->createSocketFileDescriptor(domain, socketType, protocol);
    } catch (std::runtime_error& e){
        this->logger->error(e.what());
        std::terminate();
    }
}

Socket::~Socket() {
    delete this->logger;
}

Socket& Socket::createSocketFileDescriptor(int domain, int socketType, int protocol) {
    if ((this->socketFileDescriptor = socket(domain, socketType, protocol)) < 0)
        throw std::runtime_error("Socket creation failed.");
    return *this;
}

Socket& Socket::bindSocket() {
    if (bind(this->socketFileDescriptor, (struct sockaddr *)&this->serverAddress, sizeof(serverAddress)) < 0)
        throw std::runtime_error("Socket binding failed.");
    return *this;
}

Socket& Socket::listenForConnections(int maxConnectionsNumber) {
    if (listen(this->socketFileDescriptor, maxConnectionsNumber) < 0)
        throw std::runtime_error("Socket binding failed.");
    return *this;
}

Socket& Socket::handleConnections() {
    while(true){
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int *clientFileDescriptor = new int;

        if((*clientFileDescriptor = accept(this->socketFileDescriptor, (struct sockaddr *)&clientAddress,
                                           &clientAddressLength)) < 0) {
            this->logger->warning("Accepting connection failed.");
            continue;
        }
        char addressString[clientAddressLength];
        inet_ntop(AF_INET, &clientAddress.sin_addr, addressString, clientAddressLength);
        this->logger->info("Connection Accepted from " + (std::string)inet_ntoa(clientAddress.sin_addr));

        std::thread threadId(Socket::handleClient, (void*)clientFileDescriptor);
        threadId.detach();
    }
}

void* Socket::handleClient(void* arg) {
    Logger* logger = new Logger(std::cout, DEBUG);
    int clientFileDescriptor = *((int*)arg);
    char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

    //receive request data from client and store into buffer
    logger->info("Receiving data.");
    ssize_t bytes_received = recv(clientFileDescriptor, buffer, BUFFER_SIZE, 0);
    if(bytes_received > 0) {
        logger->info("Data received.");
        //check if request is GET
        /*regex_t regex;
        regcomp(&regex, "^GET /([^ ]*) HTTP/1", REG_EXTENDED);
        regmatch_t matches[2];*/
        //new way
        std::string* responseString = new std::string();
        std::string* request = new std::string(buffer);
        try {
            Route matchedRoute = Matcher::matchRoute(*request);
            *responseString = matchedRoute.getResponseString();
        } catch (std::runtime_error& e) {
            logger->warning("Unable to match route for request");
            *responseString = Controller::notFoundResponse();
        }

        char* textResponse = new char[responseString->length() +1 ];
        strcpy(textResponse, responseString->c_str());
        size_t responseLength = strlen(textResponse);

        logger->info("Sending response data.");
        send(clientFileDescriptor, textResponse, responseLength, 0);

        /*if(regexec(&regex, buffer, 2, matches, 0) == 0) {
            size_t response_len;
            const char* textResponse =
                    "HTTP/1.0 200 OK\r\n"
                    "Content-type: text/html; charset=utf-8\r\n"
                    "\n"
                    "<!DOCTYPE html>\n"
                    "<html>\n"
                    "<head>\n"
                    "   <title>200 OK</title>\n"
                    "</head>\n"
                    "<body>\n"
                    "   <h1>Yaaay</h1>\n"
                    "   <p>Everything is hunky-dory.</p>\n"
                    "</body>\n"
                    "</html>\r\n\r\n";

            response_len = strlen(textResponse);

            logger->info("Sending response data.");
            send(clientFileDescriptor, textResponse, response_len, 0);
        }*/
//        regfree(&regex);
    }
    close(clientFileDescriptor);
    free(arg);
    free(buffer);

    return NULL;
}


