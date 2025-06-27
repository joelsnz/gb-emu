#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define TILE_SIZE 16

void lcd_test();
void lcd_init();
void lcd_set_scale(uint8_t scale);
void lcd_draw_tile(uint8_t x, uint8_t y, uint8_t tile[TILE_SIZE]);
void lcd_draw_background(uint8_t tilemap[32][32][TILE_SIZE]);
void lcd_draw_window(uint8_t x, uint8_t y, uint32_t color);

#endif // LCD_H
