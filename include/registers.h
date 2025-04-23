#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

typedef struct {
  union {
    struct {
      uint8_t a;
      uint8_t f;
    };
    uint16_t af;  
  };
  union {
    struct {
      uint8_t b;
      uint8_t c;
    };
    uint16_t bc;  
  };
  union {
    struct {
      uint8_t d;
      uint8_t e;
    };
    uint16_t de;  
  };
  union {
    struct {
      uint8_t h;
      uint8_t l;
    };
    uint16_t hl;  
  };
  uint16_t sp;
  uint16_t pc;
} registers_t;

void init_r8(registers_t *r, uint8_t **table);
void init_r16(registers_t *r, uint16_t **table);
void init_r16mem(registers_t *r, uint16_t **table);
void init_r16stk(registers_t *r, uint16_t **table);

#endif // REGISTERS_H
