#ifndef CPU_H
#define CPU_H

#include "emulator.h"
#include "registers.h"

#include <stdint.h>

typedef struct cpu_t {
  registers_t registers;
  uint8_t *r8[8];
  uint16_t *r16[4];
  uint16_t *r16mem[4];
  uint16_t *r16stk[4];
  uint8_t ime;
  uint8_t opcode;
  uint64_t cycles;
} cpu_t;

void init_cpu(cpu_t *cpu);
void get_opcode(const emu_t *emu);
void cpu_step(const emu_t *emu);

uint8_t *get_lower_r8(const emu_t *emu);
uint8_t *get_middle_r8(const emu_t *emu);
uint8_t get_imm8(const emu_t *emu);
uint16_t get_imm16(const emu_t *emu);
uint16_t *get_r16(const cpu_t *cpu);

uint16_t get_r16mem(cpu_t *cpu);
uint16_t *get_r16stk(const cpu_t *cpu);
uint8_t get_tgt3(const cpu_t *cpu);
uint8_t get_b3(const cpu_t *cpu);
uint8_t get_cond(const cpu_t *cpu);

#endif // CPU_H
