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

    this->regexString = this->httpMethodName[httpMethod] + " " + regexRoute + " HTTP/1";
            //"^GET /([^ ]*) HTTP/1.1"
}

std::string Route::getRegexString() {
    return this->regexString;
}

std::string Route::getResponseString(std::vector<std::string> args) {
    return this->controllerFunctionPointer(std::move(args));
}

bool Route::doesRegexMatch(std::string) {
//    std::regex regExpr = this->regexString;
    return false;
}

