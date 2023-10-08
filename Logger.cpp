#include "logger.h"
#include <iomanip>
#include <ctime>

Logger::Logger(std::ostream& outputStream, LoggerLevel loggerLevel) :outputStream(outputStream) {
    this->loggerLevel = loggerLevel;
}

void Logger::log(LoggerLevel level, const std::string& message) {
    time_t now = time(NULL);
    struct tm* currentTime = localtime(&now);

    if(level <= this->loggerLevel){
        this->outputStream << "[" << std::put_time(currentTime, "%FT%T") << "]" <<
                            this->levelNames[level] << ": " << message << std::endl;
    }
}

void Logger::emergency(const std::string& message) {
    this->log(EMERGENCY, message);
}

void Logger::alert(const std::string& message) {
    this->log(ALERT, message);
}

void Logger::critical(const std::string& message) {
    this->log(CRITICAL, message);
}

void Logger::error(const std::string& message) {
    this->log(ERROR, message);
}

void Logger::warning(const std::string& message) {
    this->log(WARNING, message);
}

void Logger::notice(const std::string& message) {
    this->log(NOTICE, message);
}

void Logger::info(const std::string& message) {
    this->log(INFO, message);
}

void Logger::debug(const std::string& message) {
    this->log(DEBUG, message);
}
