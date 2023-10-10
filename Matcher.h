#ifndef WEBSERVER_MATCHER_H
#define WEBSERVER_MATCHER_H

#include <map>
#include "Route.h"

class Matcher {
private:
    std::vector<Route>* routeList;
public:
    Matcher();
    ~Matcher();
    static Matcher& getInstance();
    Matcher& addRoute(const Route& route);
    Matcher& addRoute(HTTP_METHOD httpMethod, std::string subUrl, std::string name,
                      std::string (*controllerFunction)(std::vector<std::string>),
                      std::vector<std::string> controllerFunctionArgs);
    Matcher& addGetRoute(std::string subUrl, std::string name, std::string (*controllerFunction)(std::vector<std::string>),
                         std::vector<std::string> controllerFunctionArgs);
    Matcher& addPostRoute(std::string subUrl, std::string name, std::string (*controllerFunction)(std::vector<std::string>),
                          std::vector<std::string> controllerFunctionArgs);
    Matcher& addPutRoute(std::string subUrl, std::string name, std::string (*controllerFunction)(std::vector<std::string>),
                         std::vector<std::string> controllerFunctionArgs);
    Matcher& addDeleteRoute(std::string subUrl, std::string name, std::string (*controllerFunction)(std::vector<std::string>),
                            std::vector<std::string> controllerFunctionArgs);
    Matcher& addPatchRoute(std::string subUrl, std::string name, std::string (*controllerFunction)(std::vector<std::string>),
                           std::vector<std::string> controllerFunctionArgs);
    static Route matchRoute(std::string subUrl);
};

#endif //WEBSERVER_MATCHER_H
