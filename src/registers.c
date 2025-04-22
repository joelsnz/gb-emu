#include "registers.h"

#include <stdio.h>

void init_r8(registers_t *r, uint8_t **table) {
  table[0] = &r->b;
  table[1] = &r->c;
  table[2] = &r->d;
  table[3] = &r->e;
  table[4] = &r->h;
  table[5] = &r->l;
  table[6] = NULL;
  table[7] = &r->a;
}

void init_r16(registers_t *r, uint16_t **table) {
  table[0] = &r->bc;
  table[1] = &r->de;
  table[2] = &r->hl;
  table[3] = &r->sp;
}

void init_r16mem(registers_t *r, uint16_t **table) {
  table[0] = &r->bc;
  table[1] = &r->de;
  table[2] = &r->hl; // hli
  table[3] = &r->hl; // hld
}
