#include "miscellaneous.h"

#include "flags.h"

void swap(cpu_t *cpu) {
  uint8_t *reg = get_lower_r8(cpu);
  uint8_t result = (*reg << 4) | (*reg >> 4);

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

  *reg = result;
}

void daa(cpu_t *cpu) {
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

void cpl(cpu_t *cpu) {
  SET_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  cpu->registers.a = ~cpu->registers.a;
}

void ccf(cpu_t *cpu) {
  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(ISSET_FLAG(cpu, CARRY_FLAG)) CLEAR_FLAG(cpu, CARRY_FLAG);
  else SET_FLAG(cpu, CARRY_FLAG);
}

void scf(cpu_t *cpu) {
  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  SET_FLAG(cpu, CARRY_FLAG);
}

void nop(cpu_t *cpu) { ; }
