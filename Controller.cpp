//
// Created by dinta on 10.10.2023.
//

#include "Controller.h"

std::string Controller::rootResponse(std::vector<std::string> args) {
    return "HTTP/1.0 200 OK\r\n"
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
}

std::string Controller::notFoundResponse(std::vector<std::string> args) {
    return "HTTP/1.0 404 Not Found\r\n"
           "Content-type: text/html; charset=utf-8\r\n"
           "\n"
           "<!DOCTYPE html>\n"
           "<html>\n"
           "<head>\n"
           "   <title>404 Not Found</title>\n"
           "</head>\n"
           "<body>\n"
           "   <h1>404 Not Found</h1>\n"
           "</body>\n"
           "</html>\r\n\r\n";
}