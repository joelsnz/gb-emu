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
void init_bit_list(void);
void init_call_list(cpu_t *cpu);
void init_jump_list(cpu_t *cpu);
void init_load_list(void);
void init_misc_list(void);
void init_shifts_list(void);
void init_instr_list(cpu_t *cpu);

#endif // INSTRUCTIONS_H