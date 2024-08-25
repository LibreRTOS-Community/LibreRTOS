cmake_minimum_required(VERSION 3.29)

project(LibreRTOS VERSION 0.0.1 DESCRIPTION "LibreRTOS Project")

set(CMAKE_C_STANDARD 11)

include_directories(include)

set(SRC_FILES 
    "port.h"
)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

