#include "flags.h"

#include "arithmetic.h"

uint8_t get_value8(const cpu_t *cpu) {
  const uint8_t reg = cpu->opcode & 0x07;

  if (cpu->opcode & 0x40) // imm8 value
    return cpu->memory[cpu->registers.pc + 1];

  return reg == 0x06 // r8 value
    ? cpu->memory[cpu->registers.hl]
    : *cpu->r8[reg];
}

// 8-bit ALU
void add(cpu_t *cpu) {
  uint8_t value = get_value8(cpu);

  const uint16_t result = cpu->registers.a + value;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG);

  const uint8_t half_carry =
    (cpu->registers.a & 0x0F) + (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.a = (uint8_t) result;
}

void adc(cpu_t *cpu) {
  uint8_t value = get_value8(cpu);

  const uint16_t result =
    cpu->registers.a + value + ISSET_FLAG(cpu, CARRY_FLAG);

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG);

  const uint8_t half_carry = (cpu->registers.a & 0x0F)
    + (value & 0x0F) + ISSET_FLAG(cpu, CARRY_FLAG) > 0x0F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.a = (uint8_t) result;
}

void sub(cpu_t *cpu) {
  uint8_t value = get_value8(cpu);

  const uint16_t result = cpu->registers.a - value;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  SET_FLAG(cpu, NEGATIVE_FLAG);

  const uint8_t half_carry =
    (cpu->registers.a & 0x0F) - (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.a = (uint8_t) result;
}

void sbc(cpu_t *cpu) {
  uint8_t value = get_value8(cpu);

  const uint16_t result =
    cpu->registers.a - value - ISSET_FLAG(cpu, CARRY_FLAG);

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  SET_FLAG(cpu, NEGATIVE_FLAG);

  const uint8_t half_carry = (cpu->registers.a & 0x0F)
  - (value & 0x0F) - ISSET_FLAG(cpu, CARRY_FLAG) > 0x0F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.a = (uint8_t) result;
}

void and(cpu_t *cpu) {
  uint8_t value = get_value8(cpu);

  const uint8_t result = cpu->registers.a & value;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG);
  SET_FLAG(cpu, HALFCARRY_FLAG);
  CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.a = (uint8_t) result;
}

void or(cpu_t *cpu) {
  uint8_t value = get_value8(cpu);

  const uint8_t result = cpu->registers.a | value;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

  cpu->registers.a = (uint8_t) result;
}

void xor(cpu_t *cpu) {
  const uint8_t reg = cpu->opcode & 0x07;

  uint8_t value = 0;
  if (cpu->opcode & 0x40)
    value = reg == 0x06 ? cpu->memory[cpu->registers.hl] : *cpu->r8[reg];
  else value = cpu->memory[cpu->registers.pc + 1];

  const uint8_t result = cpu->registers.a ^ value;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

  cpu->registers.a = (uint8_t) result;
}

void cp(cpu_t *cpu) {
  uint8_t value = get_value8(cpu);

  const uint16_t result = cpu->registers.a - value;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  SET_FLAG(cpu, NEGATIVE_FLAG);

  const uint8_t half_carry = (cpu->registers.a & 0x0F) - (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);
}

void inc(cpu_t *cpu) {
  const uint8_t *reg = cpu->r8[cpu->opcode & 0x07];

  if(*reg) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG);

  const uint8_t half_carry = (*reg & 0x0F) == 0x0F;
  if(half_carry) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  *reg++;
}

void dec(cpu_t *cpu) {
  const uint8_t *reg = cpu->r8[cpu->opcode & 0x07];

  if(*reg) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  SET_FLAG(cpu, NEGATIVE_FLAG);

  const uint8_t half_carry = (*reg & 0x0F) == 0x00;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  *reg--;
}

// 16-bit arithmetic
void addhl(cpu_t *cpu) {
  const uint16_t value = *cpu->r16[(cpu->opcode & 0x30) >> 4];
  const uint32_t result = cpu->registers.hl + value;

  CLEAR_FLAG(cpu, NEGATIVE_FLAG);

  const uint16_t half_carry =
    (cpu->registers.hl & 0x000F) + (value & 0x000F) > 0x000F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT16_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.hl = result;
}

/*void addsp(cpu_t *cpu) {
  const uint16_t value = *cpu->r16[(cpu->opcode & 0x30) >> 4];
  const uint32_t result = cpu->registers.sp + value;

  CLEAR_FLAG(cpu, ZERO_FLAG | NEGATIVE_FLAG);

  const uint16_t half_carry =
    (cpu->registers.sp & 0x000F) + (value & 0x000F) > 0x000F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT16_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.sp = result;
}*/

void inc16(cpu_t *cpu) {
  cpu->r16[(cpu->opcode & 0x30) >> 4]++;
}

void dec16(cpu_t *cpu) {
  cpu->r16[(cpu->opcode & 0x30) >> 4]--;
}