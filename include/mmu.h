#ifndef MMU_H
#define MMU_H

#define MEMORY_SIZE 0x10000 // 64kb

#include "emulator.h"

#include <stdint.h>

typedef union vram_t {
  uint8_t *raw;
  struct {
    uint16_t tile_data[384];
    uint8_t tile_map[2][32][32];
  };
} vram_t;

typedef union mmu_t {
  uint8_t raw[MEMORY_SIZE];
  struct {
    uint8_t rom[0x8000];
    vram_t vram;
    uint8_t eram[0x2000];
    uint8_t wram[0x2000];
    uint8_t oam[0xA0];
    uint8_t io[0x80];
    uint8_t hram[0x7F];
    uint8_t ie;
    uint8_t if_;
  };
} mmu_t;

#endif // MMU_H
