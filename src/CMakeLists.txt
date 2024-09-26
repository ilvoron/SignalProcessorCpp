cmake_minimum_required(VERSION 3.5)

set(DIRS "core" "gen" "io" "proc" "test")
set(SOURCES "")
set(HEADERS "")
set(INCLUDE_DIRS "")

foreach(DIR ${DIRS})
    file(GLOB_RECURSE DIR_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.cpp")
    file(GLOB_RECURSE DIR_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.h")

    list(APPEND SOURCES ${DIR_SOURCES})
    list(APPEND HEADERS ${DIR_HEADERS})
endforeach()

add_library(lib
    ${SOURCES}
    ${HEADERS}
)

foreach(DIR ${DIRS})
    list(APPEND INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/${DIR}")
endforeach()

target_include_directories(lib PUBLIC ${INCLUDE_DIRS})