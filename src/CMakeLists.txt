set(SOURCES
  main.c
  flags.c
  registers.c
  cpu.c
  interrupt.c
  rom.c
  lcd.c
  ppu.c
  common.c
)

add_subdirectory(instructions)

add_executable(xgb)
target_sources(xgb PRIVATE ${SOURCES})
target_include_directories(xgb PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(xgb PRIVATE lib instructions)
