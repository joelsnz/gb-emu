cmake_minimum_required(VERSION 3.20)
project(xgb)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

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
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
