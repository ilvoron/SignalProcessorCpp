cmake_minimum_required(VERSION 3.5)
project(SignalProcceser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_subdirectory(src)

add_executable(signal main.cpp)
target_link_libraries(signal lib)