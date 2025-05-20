#include "lcd.h"

#include "ppu.h"

#include <SDL3/SDL.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static SDL_Event event;

uint8_t lcd_init(void) {
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) return 0;

  window = SDL_CreateWindow("xgb", LCD_WIDTH * WINDOW_SCALE,
                            LCD_HEIGHT * WINDOW_SCALE, 0);
  if(window == NULL) {
    SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
    return -2;
  }

  renderer = SDL_CreateRenderer(window, NULL);
  if(renderer == NULL) {
    SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
    return -3;
  }

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_TARGET, LCD_WIDTH,
                              LCD_HEIGHT);
  if(texture == NULL) {
    SDL_Log("SDL_CreateTexture error: %s", SDL_GetError());
    return -4;
  }

  return 0;
}

uint8_t lcd_step() {
  if(SDL_PollEvent(&event) > 0) {
    switch(event.type) {
    case SDL_EVENT_QUIT:
      lcd_quit();
      return 0;
    default:
      break;
    }
  }

  lcd_render();
  return 1;
}

void lcd_render() { ; }

void lcd_quit(void) {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
