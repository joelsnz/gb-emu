#include "shifts.h"

#include "cpu.h"
#include "flags.h"

void rlca(cpu_t *cpu) {
  uint8_t result = cpu->registers.a << 1;

  CLEAR_FLAG(cpu, ZERO_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(cpu->registers.a & 0x80) {
    SET_FLAG(cpu, CARRY_FLAG);
    result++;
  } else {
    CLEAR_FLAG(cpu, CARRY_FLAG);
  }

  cpu->registers.a = result;
}

void rla(cpu_t *cpu) {
  uint8_t result = cpu->registers.a << 1;

  result += ISSET_FLAG(cpu, CARRY_FLAG);

  CLEAR_FLAG(cpu, ZERO_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(cpu->registers.a & 0x80) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.a = result;
}

void rrca(cpu_t *cpu) {
  uint8_t result = cpu->registers.a >> 1;

  CLEAR_FLAG(cpu, ZERO_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(cpu->registers.a & 0x01) {
    SET_FLAG(cpu, CARRY_FLAG);
    result |= 0x80;
  } else {
    CLEAR_FLAG(cpu, CARRY_FLAG);
  }

  cpu->registers.a = result;
}

void rra(cpu_t *cpu) {
  uint8_t result = cpu->registers.a >> 1;

  result += ISSET_FLAG(cpu, CARRY_FLAG) ? 0x80 : 0x00;

  CLEAR_FLAG(cpu, ZERO_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(cpu->registers.a & 0x01) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.a = result;
}

void rlc(cpu_t *cpu) {
  uint8_t *reg = *get_lower_r8(cpu);
  uint8_t result = *reg << 1;

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x80) {
    SET_FLAG(cpu, CARRY_FLAG);
    result++;
  } else {
    CLEAR_FLAG(cpu, CARRY_FLAG);
  }

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  *reg = result;
}

void rl(cpu_t *cpu) {
  uint8_t *reg = *get_lower_r8(cpu);
  uint8_t result = *reg << 1;

  result += ISSET_FLAG(cpu, CARRY_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x80) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  *reg = result;
}

void rrc(cpu_t *cpu) {
  uint8_t *reg = *get_lower_r8(cpu);
  uint8_t result = *reg >> 1;

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x01) {
    SET_FLAG(cpu, CARRY_FLAG);
    result |= 0x80;
  } else {
    CLEAR_FLAG(cpu, CARRY_FLAG);
  }

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  *reg = result;
}

void rr(cpu_t *cpu) {
  uint8_t *reg = *get_lower_r8(cpu);
  uint8_t result = *reg >> 1;

  result += ISSET_FLAG(cpu, CARRY_FLAG) ? 0x80 : 0x00;

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x01) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  *reg = result;
}

void sla(cpu_t *cpu) {
  uint8_t *reg = *get_lower_r8(cpu);
  uint8_t result = *reg << 1;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x80) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  *reg = result;
}

void sra(cpu_t *cpu) {
  uint8_t *reg = *get_lower_r8(cpu);
  uint8_t result = (*reg >> 1) | (*reg & 0x80);

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x01) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  *reg = result;
}

void srl(cpu_t *cpu) {
  uint8_t *reg = *get_lower_r8(cpu);
  uint8_t result = *reg >> 1;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x01) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  *reg = result;
}
