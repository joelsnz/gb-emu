#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define LCD_WIDTH 160
#define LCD_HEIGHT 144
#define WINDOW_SCALE 4

#include "cpu.h"

typedef struct {
  uint8_t ly;
  uint8_t lyc;
  uint8_t stat;
} lcd_t;

uint8_t lcd_init(lcd_t* lcd, cpu_t* cpu);
uint8_t lcd_step(void);
void lcd_render(void);
void lcd_quit(void);

#endif // LCD_H
