#include "lcd.h"

#include "SDL3/SDL.h"

#include <stdio.h>
#include <stdlib.h>

static SDL_Window *window = NULL;
static SDL_Surface *surface = NULL;
static SDL_Rect pixel = {0, 0, WINDOW_SCALE, WINDOW_SCALE};

void lcd_init() {
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("xgb", LCD_WIDTH * WINDOW_SCALE,
                            LCD_HEIGHT * WINDOW_SCALE, 0);
  surface = SDL_GetWindowSurface(window);
}

void lcd_draw_frame() {
  for(pixel.x = 0; pixel.x < LCD_WIDTH * WINDOW_SCALE;
      pixel.x += WINDOW_SCALE)
    for(pixel.y = 0; pixel.y < LCD_HEIGHT * WINDOW_SCALE;
        pixel.y += WINDOW_SCALE)
      SDL_FillSurfaceRect(surface, &pixel, (Uint32)rand());

  SDL_UpdateWindowSurface(window);
}

void lcd_test() {
  lcd_init();

  lcd_draw_frame();

  SDL_Delay(5000);
}
