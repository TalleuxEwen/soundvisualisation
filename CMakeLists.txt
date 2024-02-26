cmake_minimum_required(VERSION 3.25.1)
project(soundvisualisation)

set(CMAKE_CXX_STANDARD 14)

add_executable(soundvisualisation
        src/main.cpp
        src/Parser/Parser.cpp
        src/Parser/Parser.hpp
        src/SessionProperties/SessionProperties.cpp
        src/SessionProperties/SessionProperties.hpp
        src/Session/Session.cpp
        src/Session/Session.hpp
        src/Colors.hpp
        src/Network/Network.cpp
        src/Network/Network.hpp)
