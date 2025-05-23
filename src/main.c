#include "cpu.h"
#include "lcd.h"
#include "rom.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  cpu_t cpu;
  lcd_t lcd;
  init_cpu(&cpu);
  if(lcd_init(&lcd, &cpu) < 0) return 0;

  SDL_Event event;
  uint8_t running = 1;
  while(running) {
    // cpu_step();
    running = lcd_step();
  }

  return 0;
}