#ifndef LCD_H
#define LCD_H

#include "SDL3/SDL_surface.h"
#include "emulator.h"

#include <stdint.h>

#define TILE_SIZE 16
#define LCD_WIDTH 160
#define LCD_HEIGHT 144

enum lcdc_t {
  BG_WDW_ENABLE,
  OBJ_ENABLE,
  OBJ_SIZE,
  BG_TILE_MAP,
  BG_WDW_TILES,
  WDW_ENABLE,
  WDW_TILE_MAP,
  LCD_PPU_ENABLE
};

typedef struct lcd_t {
  uint8_t lcdc;
  uint8_t status;
  uint8_t scy;
  uint8_t scx;
  uint8_t ly;
  uint8_t lyc;
  uint8_t dma;
  uint8_t bgp;
  uint8_t obp0;
  uint8_t obp1;
  uint8_t wy;
  uint8_t wx;
} lcd_t;

SDL_Surface *lcd_init(const lcd_t *lcd, uint8_t scale);

#endif // LCD_H
