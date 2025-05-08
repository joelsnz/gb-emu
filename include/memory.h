#ifndef MEMORY_H
#define MEMORY_H

#define MEMORY_SIZE 0x10000 // 64kb

#include <stdint.h>

typedef union {
  uint8_t raw[MEMORY_SIZE];
  struct {
    uint8_t rom[0x8000];
    uint8_t vram[0x2000];
    uint8_t eram[0x2000];
    uint8_t wram[0x2000];
    uint8_t oam[0xA0];
    uint8_t io[0x80];
    uint8_t hram[0x7F];
    uint8_t ie;
    uint8_t if_;   
  };
} memory_t;

#endif // MEMORY_H
