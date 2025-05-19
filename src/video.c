#include "video.h"

#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

uint8_t init_video(void) {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) return 0;

  window = SDL_CreateWindow("xgb", SCREEN_WIDTH * WINDOW_SCALE,
                            SCREEN_HEIGHT * WINDOW_SCALE, 0);
  if(!window) return 0;

  renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) return 0;

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
  // render_video();
  return 1;
}

void render_video(uint32_t framebuffer[SCREEN_HEIGHT][SCREEN_WIDTH]) {
  // SDL_UpdateTexture(texture, NULL, framebuffer, SCREEN_WIDTH * sizeof(uint32_t));
  SDL_RenderClear(renderer);
  // SDL_RenderTexture(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void quit_video(void) {
  SDL_DestroyWindow(window);
  SDL_Quit();
}
