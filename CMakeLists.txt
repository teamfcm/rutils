cmake_minimum_required(VERSION 3.8)
project(rutils)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17")
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        RutilsException.hpp
        Singleton.hpp
        IniManager.hpp RutilsParsingTools.hpp)

add_executable(rutils ${SOURCE_FILES})
target_link_libraries(rutils -lstdc++fs)