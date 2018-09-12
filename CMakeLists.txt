cmake_minimum_required(VERSION 2.8.9)
project(smengine)

file(GLOB SOURCES "*.c")
add_library(smengine STATIC "smengine.c")
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories(
"${PROJECT_SOURCE_DIR}"

)
