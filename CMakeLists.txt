cmake_minimum_required(VERSION 3.20)
project(xgb)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCES
    src/main.c
    src/cpu.c
    src/flags.c
    src/registers.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)