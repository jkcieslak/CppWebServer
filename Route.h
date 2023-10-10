#ifndef WEBSERVER_ROUTE_H
#define WEBSERVER_ROUTE_H

#include <string>
#include <utility>
#include <vector>

enum HTTP_METHOD {
    GET = 0,
    HEAD = 1,
    POST = 2,
    PUT = 3,
    DELETE = 4,
    CONNECT = 5,
    OPTIONS = 6,
    TRACE = 7,
    PATCH = 8
};

class Route{
private:
    std::string httpMethodName[9] = { "GET", "HEAD", "POST", "PUT", "DELETE", "CONNECT",
                                      "OPTIONS", "TRACE", "PATCH"};
    HTTP_METHOD requestHttpMethod;
    std::string requestSubUrl;
    std::string routeName;
    std::string (*controllerFunctionPointer)(std::vector<std::string>);
    std::vector<std::string> controllerFunctionArgs;
    std::string regexString;
public:
    Route(HTTP_METHOD httpMethod, std::string subUrl, std::string name,
          std::string (*controllerFunctionPointer)(std::vector<std::string>),
          std::vector<std::string> routeArgs);
    std::string getRegexString();
    std::string getResponseString(std::vector<std::string> args = std::vector<std::string>());
    bool doesRegexMatch(std::string);
};

#endif //WEBSERVER_ROUTE_H
