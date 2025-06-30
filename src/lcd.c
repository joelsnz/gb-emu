#include "lcd.h"

#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"

static SDL_Window *window = NULL;
static SDL_Surface *surface = NULL;

SDL_Surface *lcd_init(const lcd_t *lcd, uint8_t scale) {
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("xgb", LCD_WIDTH * scale,
                            LCD_HEIGHT * scale, 0);
  return (surface = SDL_GetWindowSurface(window));
}
