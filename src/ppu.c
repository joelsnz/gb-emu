#include "ppu.h"

#include "SDL3/SDL_rect.h"
#include "common.h"
#include "lcd.h"
#include "mmu.h"

static uint8_t window_scale = 1;
static uint32_t palette[4] = {0xFF3a5122, 0xFF5d782e, 0xFF919b3a,
                              0xFFb5af42};
static SDL_Surface *surface = NULL;

static SDL_Rect scale(SDL_Rect rect) {
  rect.x *= window_scale;
  rect.y *= window_scale;
  rect.w *= window_scale;
  rect.h *= window_scale;

  return rect;
}

void set_scale(uint8_t scale) { window_scale = scale; }

void ppu_init(emu_t *emu) {
  surface = lcd_init(emu->lcd, window_scale);
}

void lcd_draw_tile(uint8_t x, uint8_t y, uint8_t tile[TILE_SIZE]) {
  for(int row = 0; row < 8; row++) {
    uint8_t lsb = tile[row * 2];
    uint8_t msb = tile[(row * 2) + 1];

    for(int col = 0; col < 8; col++) {
      uint8_t bit = 7 - col; // column 0 on msb
      uint8_t color = ((msb >> bit) & 1) << 1 | ((lsb >> bit) & 1);

      SDL_Rect pixel = scale((SDL_Rect){x + col, y + row, 1, 1});
      SDL_FillSurfaceRect(surface, &pixel, palette[color]);
    }
  }
}

void lcd_draw_background(emu_t *emu) {
  lcd_t *lcd = emu->lcd;
  mmu_t *mmu = emu->mmu;
  vram_t *vram = &mmu->vram;
  uint8_t *lcdc = &lcd->lcdc;
  SDL_Rect bg = {0, 0, LCD_WIDTH, LCD_HEIGHT}; // starts with blank bg

  SDL_FillSurfaceRect(surface, &bg, palette[0]);
}

void lcd_draw_window(uint8_t x, uint8_t y, uint32_t color) {
  SDL_Rect wdw =
      scale((SDL_Rect){x, y, LCD_WIDTH - x, LCD_HEIGHT - y});
  SDL_FillSurfaceRect(surface, &wdw, color);
}
