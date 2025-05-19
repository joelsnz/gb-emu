#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define WINDOW_SCALE 4

uint8_t init_video(void);
uint8_t video_step(void);
void render_video(uint32_t framebuffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
void quit_video(void);

#endif // GRAPHICS_H
