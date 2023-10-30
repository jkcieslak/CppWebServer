#include "Matcher.h"

#include <utility>
#include <stdexcept>

Matcher::Matcher() {
    this->routeList = new std::vector<Route>();
}

Matcher::~Matcher() {
    delete this->routeList;
}

Matcher& Matcher::getInstance(){
    static Matcher instance_;
    return instance_;
}

Matcher& Matcher::addRoute(const Route& route) {
    this->routeList->push_back(route);
    return *this;
}

Matcher& Matcher::addRoute(HTTP_METHOD httpMethod, std::string subUrl, std::string name,
                           std::string (*controllerFunction)(std::vector<std::string>),
                           std::vector<std::string> controllerFunctionArgs) {
    Route* route = new Route(httpMethod, std::move(subUrl), std::move(name), controllerFunction, std::move(controllerFunctionArgs));
    this->routeList->push_back(*route);
    return *this;
}

Matcher& Matcher::addGetRoute(std::string subUrl, std::string name, std::string (*controllerFunction)(std::vector<std::string>),
                              std::vector<std::string> controllerFunctionArgs) {
    return this->addRoute(GET, std::move(subUrl), std::move(name), controllerFunction, std::move(controllerFunctionArgs));
}

Matcher& Matcher::addPostRoute(std::string subUrl, std::string name, std::string (*controllerFunction)(std::vector<std::string>),
                              std::vector<std::string> controllerFunctionArgs) {
    return this->addRoute(POST, std::move(subUrl), std::move(name), controllerFunction, std::move(controllerFunctionArgs));
}

Matcher& Matcher::addPutRoute(std::string subUrl, std::string name, std::string (*controllerFunction)(std::vector<std::string>),
                              std::vector<std::string> controllerFunctionArgs) {
    return this->addRoute(PUT, std::move(subUrl), std::move(name), controllerFunction, std::move(controllerFunctionArgs));
}

Matcher& Matcher::addDeleteRoute(std::string subUrl, std::string name, std::string (*controllerFunction)(std::vector<std::string>),
                              std::vector<std::string> controllerFunctionArgs) {
    return this->addRoute(DELETE, std::move(subUrl), std::move(name), controllerFunction, std::move(controllerFunctionArgs));
}

Matcher& Matcher::addPatchRoute(std::string subUrl, std::string name, std::string (*controllerFunction)(std::vector<std::string>),
                              std::vector<std::string> controllerFunctionArgs) {
    return this->addRoute(PATCH, std::move(subUrl), std::move(name), controllerFunction, std::move(controllerFunctionArgs));
}

Route Matcher::matchRoute(std::string subUrl) {
    for(auto & route : *Matcher::getInstance().routeList) {
        if(subUrl.find(route.getMatchString()) != std::string::npos)
            return route;
    }
    throw std::runtime_error("404 Not Found");
}

