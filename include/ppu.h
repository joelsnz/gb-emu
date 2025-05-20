#ifndef PPU_H
#define PPU_H

#include <stdint.h>

static const uint32_t palette[4] = {
    0xFFE6F0FF,  // very light pink
    0xFFB3D1FF,  // light pink
    0xFF66A3FF,  // dark pink
    0xCC0066FF   // very dark pink
};

void ppu_step(void);

#endif //PPU_H
