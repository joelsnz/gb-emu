#include "arithmetic.h"

#include "flags.h"

// 8-bit ALU
void add(cpu_t *cpu) {
  uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(cpu) : *get_lower_r8(cpu);

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

  cpu->registers.a = (uint8_t)result;
}

void adc(cpu_t *cpu) {
  uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(cpu) : *get_lower_r8(cpu);

  const uint16_t result =
      cpu->registers.a + value + ISSET_FLAG(cpu, CARRY_FLAG);

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG);

  const uint8_t half_carry = (cpu->registers.a & 0x0F) +
                                 (value & 0x0F) +
                                 ISSET_FLAG(cpu, CARRY_FLAG) >
                             0x0F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.a = (uint8_t)result;
}

void sub(cpu_t *cpu) {
  uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(cpu) : *get_lower_r8(cpu);

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

  cpu->registers.a = (uint8_t)result;
}

void sbc(cpu_t *cpu) {
  uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(cpu) : *get_lower_r8(cpu);

  const uint16_t result =
      cpu->registers.a - value - ISSET_FLAG(cpu, CARRY_FLAG);

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  SET_FLAG(cpu, NEGATIVE_FLAG);

  const uint8_t half_carry = (cpu->registers.a & 0x0F) -
                                 (value & 0x0F) -
                                 ISSET_FLAG(cpu, CARRY_FLAG) >
                             0x0F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.a = (uint8_t)result;
}

void and_(cpu_t *cpu) {
  uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(cpu) : *get_lower_r8(cpu);

  const uint8_t result = cpu->registers.a & value;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG);
  SET_FLAG(cpu, HALFCARRY_FLAG);
  CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.a = (uint8_t)result;
}

void or_(cpu_t *cpu) {
  uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(cpu) : *get_lower_r8(cpu);

  const uint8_t result = cpu->registers.a | value;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

  cpu->registers.a = (uint8_t)result;
}

void xor_(cpu_t *cpu) {
  uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(cpu) : *get_lower_r8(cpu);

  const uint8_t result = cpu->registers.a ^ value;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

  cpu->registers.a = (uint8_t)result;
}

void cp(cpu_t *cpu) {
  uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(cpu) : *get_lower_r8(cpu);

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
}

void inc(cpu_t *cpu) {
  const uint8_t *reg = get_middle_r8(cpu);

  if(*reg) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG);

  const uint8_t half_carry = (*reg & 0x0F) == 0x0F;
  if(half_carry) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  *reg++;
}

void dec(cpu_t *cpu) {
  const uint8_t *reg = get_middle_r8(cpu);

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
  const uint16_t value  = *get_r16(cpu);
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

void addsp(cpu_t *cpu) {
  const uint8_t value   = get_imm8(cpu);
  const uint32_t result = cpu->registers.sp + value;

  CLEAR_FLAG(cpu, ZERO_FLAG | NEGATIVE_FLAG);

  const uint16_t half_carry =
      (cpu->registers.sp & 0x000F) + (value & 0x000F) > 0x000F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT16_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.sp = result;
}

void inc16(cpu_t *cpu) { (*get_r16(cpu))++; }

void dec16(cpu_t *cpu) { (*get_r16(cpu))--; }
