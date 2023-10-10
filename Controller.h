//
// Created by dinta on 10.10.2023.
//

#ifndef WEBSERVER_CONTROLLER_H
#define WEBSERVER_CONTROLLER_H


#include <string>
#include <vector>

class Controller {
public:
    static std::string rootResponse(std::vector<std::string> args = std::vector<std::string>());
    static std::string notFoundResponse(std::vector<std::string> args = std::vector<std::string>());
};


#endif //WEBSERVER_CONTROLLER_H
