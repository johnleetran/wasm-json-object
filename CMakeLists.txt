cmake_minimum_required(VERSION 3.12.0)

# set the project name and version
project(json-object VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
if(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Release Build")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

if(WASM)
    message(STATUS "WEB ASSEMBLY TARGET IS ON")
    add_library(${PROJECT_NAME} STATIC main.cpp)
else()
    message(STATUS "Building for desktop")
    add_executable(${PROJECT_NAME} main.cpp)
endif()
