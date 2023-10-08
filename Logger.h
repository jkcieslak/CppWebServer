#ifndef WEBSERVER_LOGGER_H
#define WEBSERVER_LOGGER_H

#include <iostream>
#include <string>

enum LoggerLevel {
    EMERGENCY = 0,
    ALERT = 1,
    CRITICAL = 2,
    ERROR = 3,
    WARNING = 4,
    NOTICE = 5,
    INFO = 6,
    DEBUG = 7
};

class Logger {
private:
    std::ostream& outputStream = std::cout;
    LoggerLevel loggerLevel;
    std::string levelNames[8] =
            {"EMERGENCY", "ALERT", "CRITICAL", "ERROR", "WARNING", "NOTICE", "INFO", "DEBUG"};
public:
    explicit Logger(std::ostream& outputStream, LoggerLevel loggerLevel = ERROR);
    void log(LoggerLevel level, const std::string& message);
    void emergency(const std::string& message);
    void alert(const std::string& message);
    void critical(const std::string& message);
    void error(const std::string& message);
    void warning(const std::string& message);
    void notice(const std::string& message);
    void info(const std::string& message);
    void debug(const std::string& message);
};

#endif //WEBSERVER_LOGGER_H
