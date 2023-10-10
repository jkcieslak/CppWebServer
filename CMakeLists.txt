cmake_minimum_required(VERSION 3.24)
project(WebServer CXX)

add_executable(WebServer tcpservercpp.cpp
        Socket.h
        Socket.cpp
        Logger.h
        Logger.cpp
        Matcher.h
        Matcher.cpp
        Route.h
        Route.cpp
        Controller.cpp Controller.h)
#SET(TARGET_H Socket.h Logger.h)
#SET(TARGET_SRC Socket.cpp Logger.cpp)
#
#target_include_directories(WebServer PUBLIC PROJECT_SOURCE_DIR)
#target_link_directories(WebServer PUBLIC PROJECT_SOURCE_DIR)

#add_library(socket Socket.cpp)
#add_library(logger Logger.cpp)

#target_link_libraries(WebServer socket logger)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CXX_STANDARD)


