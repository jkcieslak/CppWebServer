#include "Logger.h"
#include "Socket.h"

int main(int argc, char *argv[]) {
    Logger* logger = new Logger(std::cout, DEBUG);
    Socket* socketInV4 = new Socket(AF_INET, SOCK_STREAM, IPPROTO_IP, INADDR_ANY,
                                    8080);
    logger->info("Server is starting.");
    try {
        socketInV4->bindSocket().listenForConnections(10).handleConnections();
    } catch (std::runtime_error& e) {
        logger->error(e.what());
    }


    /*Socket* socketInV6 = new Socket(AF_INET6, SOCK_STREAM, IPPROTO_IPV6,
                                    INADDR_ANY, 8080);
    socketInV6->bindSocket().listenForConnections(10);
*/
    return 0;
}

