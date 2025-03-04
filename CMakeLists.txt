cmake_minimum_required(VERSION 3.20)
project(xgb)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})