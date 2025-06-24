set(INSTRUCTIONS
  instructions.c
  arithmetic.c
  miscellaneous.c
  shifts.c
  bit.c
  jump.c
  load.c
  call.c
)

add_library(instructions STATIC ${INSTRUCTIONS})
target_include_directories(instructions PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(instructions PUBLIC ${CMAKE_SOURCE_DIR}/include/instructions)
