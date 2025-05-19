cmake_minimum_required(VERSION 3.20)
project(xgb)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(lib/SDL EXCLUDE_FROM_ALL)

set(SOURCES
  src/main.c
  src/instructions/instructions.c
  src/flags.c
  src/registers.c
  src/memory.c
  src/cpu.c
  src/instructions/arithmetic.c
  src/instructions/miscellaneous.c
  src/instructions/shifts.c
  src/instructions/bit.c
  src/instructions/jump.c
  src/instructions/load.c
  src/instructions/call.c
  src/interrupt.c
  src/rom.c
  src/video.c
  src/ppu.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(xgb PRIVATE SDL3::SDL3)
