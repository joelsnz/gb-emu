#include "instructions/shifts.h"

#include "common.h"
#include "cpu.h"
#include "flags.h"

#include <stdint.h>

void rlca(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t result = cpu->registers.a << 1;

  CLEAR_BIT(cpu->registers.f,
            ZERO_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(cpu->registers.a & 0x80) {
    SET_BIT(cpu->registers.f, CARRY_FLAG);
    result++;
  } else {
    CLEAR_BIT(cpu->registers.f, CARRY_FLAG);
  }

  cpu->registers.a = result;
}

void rla(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t result = cpu->registers.a << 1;

  result += ISSET_BIT(cpu->registers.f, CARRY_FLAG);

  CLEAR_BIT(cpu->registers.f,
            ZERO_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(cpu->registers.a & 0x80) SET_BIT(cpu->registers.f, CARRY_FLAG);
  else CLEAR_BIT(cpu->registers.f, CARRY_FLAG);

  cpu->registers.a = result;
}

void rrca(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t result = cpu->registers.a >> 1;

  CLEAR_BIT(cpu->registers.f,
            ZERO_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(cpu->registers.a & 0x01) {
    SET_BIT(cpu->registers.f, CARRY_FLAG);
    result |= 0x80;
  } else {
    CLEAR_BIT(cpu->registers.f, CARRY_FLAG);
  }

  cpu->registers.a = result;
}

void rra(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t result = cpu->registers.a >> 1;

  result += ISSET_BIT(cpu->registers.f, CARRY_FLAG) ? 0x80 : 0x00;

  CLEAR_BIT(cpu->registers.f,
            ZERO_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(cpu->registers.a & 0x01) SET_BIT(cpu->registers.f, CARRY_FLAG);
  else CLEAR_BIT(cpu->registers.f, CARRY_FLAG);

  cpu->registers.a = result;
}

void rlc(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t *reg = get_lower_r8(emu);
  uint8_t result = *reg << 1;

  CLEAR_BIT(cpu->registers.f, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x80) {
    SET_BIT(cpu->registers.f, CARRY_FLAG);
    result++;
  } else {
    CLEAR_BIT(cpu->registers.f, CARRY_FLAG);
  }

  if(result) CLEAR_BIT(cpu->registers.f, ZERO_FLAG);
  else SET_BIT(cpu->registers.f, ZERO_FLAG);

  *reg = result;
}

void rl(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t *reg = get_lower_r8(emu);
  uint8_t result = *reg << 1;

  result += ISSET_BIT(cpu->registers.f, CARRY_FLAG);

  CLEAR_BIT(cpu->registers.f, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x80) SET_BIT(cpu->registers.f, CARRY_FLAG);
  else CLEAR_BIT(cpu->registers.f, CARRY_FLAG);

  if(result) CLEAR_BIT(cpu->registers.f, ZERO_FLAG);
  else SET_BIT(cpu->registers.f, ZERO_FLAG);

  *reg = result;
}

void rrc(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t *reg = get_lower_r8(emu);
  uint8_t result = *reg >> 1;

  CLEAR_BIT(cpu->registers.f, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x01) {
    SET_BIT(cpu->registers.f, CARRY_FLAG);
    result |= 0x80;
  } else {
    CLEAR_BIT(cpu->registers.f, CARRY_FLAG);
  }

  if(result) CLEAR_BIT(cpu->registers.f, ZERO_FLAG);
  else SET_BIT(cpu->registers.f, ZERO_FLAG);

  *reg = result;
}

void rr(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t *reg = get_lower_r8(emu);
  uint8_t result = *reg >> 1;

  result += ISSET_BIT(cpu->registers.f, CARRY_FLAG) ? 0x80 : 0x00;

  CLEAR_BIT(cpu->registers.f, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x01) SET_BIT(cpu->registers.f, CARRY_FLAG);
  else CLEAR_BIT(cpu->registers.f, CARRY_FLAG);

  if(result) CLEAR_BIT(cpu->registers.f, ZERO_FLAG);
  else SET_BIT(cpu->registers.f, ZERO_FLAG);

  *reg = result;
}

void sla(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t *reg = get_lower_r8(emu);
  const uint8_t result = *reg << 1;

  if(result) CLEAR_BIT(cpu->registers.f, ZERO_FLAG);
  else SET_BIT(cpu->registers.f, ZERO_FLAG);

  CLEAR_BIT(cpu->registers.f, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x80) SET_BIT(cpu->registers.f, CARRY_FLAG);
  else CLEAR_BIT(cpu->registers.f, CARRY_FLAG);

  *reg = result;
}

void sra(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t *reg = get_lower_r8(emu);
  const uint8_t result = (*reg >> 1) | (*reg & 0x80);

  if(result) CLEAR_BIT(cpu->registers.f, ZERO_FLAG);
  else SET_BIT(cpu->registers.f, ZERO_FLAG);

  CLEAR_BIT(cpu->registers.f, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x01) SET_BIT(cpu->registers.f, CARRY_FLAG);
  else CLEAR_BIT(cpu->registers.f, CARRY_FLAG);

  *reg = result;
}

void srl(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t *reg = get_lower_r8(emu);
  const uint8_t result = *reg >> 1;

  if(result) CLEAR_BIT(cpu->registers.f, ZERO_FLAG);
  else SET_BIT(cpu->registers.f, ZERO_FLAG);

  CLEAR_BIT(cpu->registers.f, NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x01) SET_BIT(cpu->registers.f, CARRY_FLAG);
  else CLEAR_BIT(cpu->registers.f, CARRY_FLAG);

  *reg = result;
}
