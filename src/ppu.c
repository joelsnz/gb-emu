#include "ppu.h"

void ppu_step() {
  static enum { HBLANK, VBLANK, OAM, VRAM } gpu_mode = HBLANK;
}
