#include "lcd.h"

#include "SDL3/SDL.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static SDL_Window *window = NULL;
static SDL_Surface *surface = NULL;

void lcd_init() {
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("xgb", LCD_WIDTH * WINDOW_SCALE,
                            LCD_HEIGHT * WINDOW_SCALE, 0);
  surface = SDL_GetWindowSurface(window);
}

static SDL_Rect scale(SDL_Rect rect) {
  rect.x *= WINDOW_SCALE;
  rect.y *= WINDOW_SCALE;
  rect.w *= WINDOW_SCALE;
  rect.h *= WINDOW_SCALE;

  return rect;
}

void lcd_draw_background() {
  SDL_Rect pixel = scale((SDL_Rect){0, 0, 1, 1});

  for(pixel.x = 0; pixel.x < LCD_WIDTH * WINDOW_SCALE;
      pixel.x += WINDOW_SCALE)
    for(pixel.y = 0; pixel.y < LCD_HEIGHT * WINDOW_SCALE;
        pixel.y += WINDOW_SCALE)
      SDL_FillSurfaceRect(surface, &pixel, (uint32_t)rand());
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
    lcd_draw_background();
    lcd_draw_window(30, 110, 0x55555555);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(20);
  }
}
