#include "lcd.h"

#include "SDL3/SDL.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static SDL_Window *window = NULL;
static SDL_Surface *surface = NULL;

#define TILE_SIZE 16

static uint32_t palette[4] = {0xFF3a5122, 0xFF5d782e, 0xFF919b3a,
                              0xFFb5af42};

static SDL_Rect scale(SDL_Rect rect) {
  rect.x *= WINDOW_SCALE;
  rect.y *= WINDOW_SCALE;
  rect.w *= WINDOW_SCALE;
  rect.h *= WINDOW_SCALE;

  return rect;
}

static void lcd_draw_tile(int x, int y, uint8_t *tile) {
  for(int row = 0; row < 8; row++) {
    uint8_t lsb = tile[row * 2];
    uint8_t msb = tile[(row * 2) + 1];
    for(int col = 0; col < 8; col++) {
      uint8_t bit = 7 - col;
      uint8_t color = ((msb >> bit) & 1) << 1 | ((lsb >> bit) & 1);
      SDL_Rect pixel = scale((SDL_Rect){x + col, y + row, 1, 1});
      SDL_FillSurfaceRect(surface, &pixel, palette[color]);
    }
  }
}

void lcd_init() {
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("xgb", LCD_WIDTH * WINDOW_SCALE,
                            LCD_HEIGHT * WINDOW_SCALE, 0);
  surface = SDL_GetWindowSurface(window);
}

void lcd_draw_background(uint8_t tilemap[32][32][TILE_SIZE]) {
  for(int i = 0; i < 32; i++)
    for(int j = 0; j < 32; j++)
      lcd_draw_tile(i * 8, j * 8, tilemap[i][j]);
}

void lcd_draw_window(int x, int y, uint32_t color) {
  SDL_Rect wdw =
      scale((SDL_Rect){x, y, LCD_WIDTH - x, LCD_HEIGHT - y});
  SDL_FillSurfaceRect(surface, &wdw, color);
}

void lcd_test() {
  lcd_init();

  int game = 1;
  while(game) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
      case SDL_EVENT_QUIT:
        game = 0;
        break;
      default:
        continue;
      }
    }
    uint8_t gameboy[TILE_SIZE] = {0x3C, 0x7E, 0x42, 0x42, 0x42, 0x42,
                                  0x42, 0x42, 0x7E, 0x5E, 0x7E, 0x0A,
                                  0x7C, 0x56, 0x38, 0x7C};
    uint8_t bg_tile[TILE_SIZE] = {0xFF, 0x00, 0x7E, 0xFF, 0x85, 0x81,
                                  0x89, 0x83, 0x93, 0x85, 0xA5, 0x8B,
                                  0xC9, 0x97, 0x7E, 0xFF};
    uint8_t background[32][32][TILE_SIZE];
    for(int i = 0; i < 32; i++)
      for(int j = 0; j < 32; j++)
        for(int k = 0; k < TILE_SIZE; k++)
          background[i][j][k] = bg_tile[k];

    lcd_draw_background(background);
    lcd_draw_window(30, 110, palette[3]);
    lcd_draw_tile(85, 77, gameboy);

    SDL_UpdateWindowSurface(window);
    SDL_Delay(20);
  }
}
