#include <regex>
#include <utility>
#include "Route.h"

Route::Route(HTTP_METHOD httpMethod, std::string subUrl, std::string name,std::string (*controllerFunctionPointer)(std::vector<std::string>),
             std::vector<std::string> routeParams): requestHttpMethod(httpMethod),
                                                    requestSubUrl(std::move(subUrl)),
                                                    routeName(std::move(name)),
                                                    controllerFunctionPointer(controllerFunctionPointer),
                                                    controllerFunctionArgs(std::move(routeParams)) {
    //replacing parameters with regex
    std::string regexRoute = this->requestSubUrl;
    for(auto & controllerFunctionArg : this->controllerFunctionArgs) {
        regexRoute.replace(regexRoute.find(controllerFunctionArg)-1, controllerFunctionArg.length()+2,
                           "\\{[^}]*\\}");
    }

    this->matchString = this->httpMethodName[httpMethod] + " " + regexRoute + " HTTP/1";
            //"^GET /([^ ]*) HTTP/1.1"
}

std::string Route::getMatchString() {
    return this->matchString;
}

std::string Route::getResponseString(std::vector<std::string> args) {
    return this->controllerFunctionPointer(std::move(args));
}

bool Route::doesSubUrlMatch(std::string subUrl) {
    for(int i = 0; i < subUrl.length(); i++) {
        this->getMatchString()[i] == subUrl[i];
    }

    return false;
}

