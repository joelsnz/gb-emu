cmake_minimum_required(VERSION 3.31)
project(xgbemu)

set(CMAKE_C_STANDARD 99)

include_directories(src)
aux_source_directory(src SRC_FILES)

add_executable(xgb ${SRC_FILES})
