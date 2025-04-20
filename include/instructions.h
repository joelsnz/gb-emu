#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

typedef struct {
  void (*instruction)(cpu_t*);
  uint8_t bytes;
  uint8_t cycles;
} instruction_t;

extern instruction_t base_instr_list[0xFF + 1];
extern instruction_t prefix_instr_list[0xFF + 1];

void init_arithmetic_list(void);
void init_instr_list(void);

#endif // INSTRUCTIONS_H
