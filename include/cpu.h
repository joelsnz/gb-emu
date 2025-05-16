#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "registers.h"
#include "memory.h"

typedef struct {
	registers_t registers;
	uint8_t *r8[8];
	uint16_t *r16[4];
	uint16_t *r16mem[4];
  uint16_t *r16stk[4];
  uint8_t ime;
	memory_t memory;
	uint8_t opcode;
  uint64_t cycles;
} cpu_t;

void init_cpu(cpu_t *cpu);
void get_opcode(cpu_t *cpu);
void cpu_step(cpu_t *cpu);

uint8_t *get_lower_r8(cpu_t *cpu);
uint8_t *get_middle_r8(cpu_t *cpu);
uint8_t get_imm8(cpu_t *cpu);
uint16_t get_imm16(cpu_t *cpu);
uint16_t *get_r16(cpu_t *cpu);

uint16_t get_r16mem(cpu_t *cpu);
uint16_t *get_r16stk(cpu_t *cpu);
uint8_t get_tgt3(cpu_t *cpu);
uint8_t get_b3(cpu_t *cpu);
uint8_t get_cond(cpu_t *cpu);

#endif //CPU_H
