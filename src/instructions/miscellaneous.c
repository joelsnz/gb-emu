#include "instructions/miscellaneous.h"

#include "flags.h"
#include "cpu.h"

void swap(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t *reg = get_lower_r8(emu);
  const uint8_t result = (*reg << 4) | (*reg >> 4);

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

  *reg = result;
}

void daa(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint16_t result = cpu->registers.a;

  if((result & 0x0F) > 0x09) result += 0x06;
  if((result & 0xF0) > 0x90) result += 0x60;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT16_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.a = result;
}

void cpl(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  SET_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  cpu->registers.a = ~cpu->registers.a;
}

void ccf(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(ISSET_FLAG(cpu, CARRY_FLAG)) CLEAR_FLAG(cpu, CARRY_FLAG);
  else SET_FLAG(cpu, CARRY_FLAG);
}

void scf(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  SET_FLAG(cpu, CARRY_FLAG);
}

void nop(const emu_t *emu) { ; }

void halt(const emu_t *emu) { ; } // tbi

void stop(const emu_t *emu) { ; } // tbi

void di(const emu_t *emu) { emu->cpu->ime = 0; }

void ei(const emu_t *emu) { emu->cpu->ime = 1; }