#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define LCD_WIDTH 160
#define LCD_HEIGHT 144
#define WINDOW_SCALE 4

uint8_t lcd_init(void);
uint8_t lcd_step(void);
void lcd_render(void);
void lcd_quit(void);

#endif // LCD_H
