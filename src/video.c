#include "video.h"

#include <SDL3/SDL.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

SDL_Color colors[4] = {
  {255, 255, 255, 255},  // white
  {192, 192, 192, 255},  // light gray
  {96,  96,  96,  255},  // dark gray
  {0,   0,   0,   255},  // black
};

SDL_Palette *palette = SDL_CreatePalette(4);

uint8_t init_video(void) {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) return 0;

  window = SDL_CreateWindow("xgb", SCREEN_WIDTH /* WINDOW_SCALE*/,
                            SCREEN_HEIGHT/* WINDOW_SCALE*/, 0);
  if(!window) return 0;

  renderer = SDL_CreateRenderer(window, NULL);
  if(!renderer) return 0;

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_INDEX8, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
  if(!texture) return 0;
  //SDL_SetPaletteColors(SDL_Alloc, palette, 0, 4);

  return 1;
}

uint8_t video_step() {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
    case SDL_EVENT_QUIT:
      quit_video();
      return 0;
      default: break;
    }
  }
  uint32_t framebuffer[SCREEN_HEIGHT][SCREEN_WIDTH] = {0};
  render_video(framebuffer);
  return 1;
}

void render_video(uint32_t framebuffer[SCREEN_HEIGHT][SCREEN_WIDTH]) {
  SDL_UpdateTexture(texture, NULL, framebuffer, SCREEN_WIDTH * sizeof(uint32_t));
  SDL_RenderClear(renderer);
  SDL_RenderTexture(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void quit_video(void) {
  SDL_DestroyWindow(window);
  SDL_Quit();
}