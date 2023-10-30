#include "Logger.h"
#include "Socket.h"
#include "Route.h"
#include "Controller.h"
#include "Matcher.h"

int main(int argc, char *argv[]) {
    Logger* logger = new Logger(std::cout, DEBUG);
    Socket* socketInV4 = new Socket(AF_INET, SOCK_STREAM, IPPROTO_IP, INADDR_ANY,
                                    8080);
    logger->info("Server is starting.");


    std::vector<std::string>* routeParams = new std::vector<std::string>();
    routeParams->insert(routeParams->end(), "argParsing");
    logger->debug("Route param: " + routeParams->at(0));
    Route* route = new Route(GET, "/regex/example/{argParsing}/", "regex_example",
                             Controller::notFoundResponse, *routeParams);

    Route* route2 = new Route(GET, "/", "home", Controller::rootResponse,
                              std::vector<std::string>());

    Matcher matcher = Matcher::getInstance();
    matcher.addRoute(*route).addRoute(*route2);

    logger->debug(route->getMatchString());
    logger->debug(route2->getMatchString());

    try {
        socketInV4->bindSocket().listenForConnections(10).handleConnections();
    } catch (std::runtime_error& e) {
        logger->error(e.what());
        std::terminate();
    }


    /*Socket* socketInV6 = new Socket(AF_INET6, SOCK_STREAM, IPPROTO_IPV6,
                                    INADDR_ANY, 8080);
    socketInV6->bindSocket().listenForConnections(10);
*/
    delete logger;
    delete socketInV4;
    return 0;
}

