cmake_minimum_required(VERSION 3.5)
project(SignalProcessorCPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif ()

set(CMAKE_SOURCE_DIR "src")
set(CMAKE_VERSION_FILE "VERSION")

file(READ "${CMAKE_VERSION_FILE}" VERSION_CONTENT)
string(STRIP "${VERSION_CONTENT}" PROJECT_VERSION)
message(STATUS "Project version: ${PROJECT_VERSION}")

add_subdirectory(${CMAKE_SOURCE_DIR})

add_executable(SignalProcessorCPP main.cpp)
target_link_libraries(SignalProcessorCPP lib)