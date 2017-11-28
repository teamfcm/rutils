cmake_minimum_required(VERSION 3.8)
project(rutils)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp RutilsException.hpp Singleton.hpp Meh.hpp IniManager.hpp)
add_executable(rutils ${SOURCE_FILES})