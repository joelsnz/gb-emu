#include "instructions/arithmetic.h"

#include <stdint.h>

#include "flags.h"
#include "cpu.h"

// 8-bit ALU
void add(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(emu) : *get_lower_r8(emu);

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

void adc(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(emu) : *get_lower_r8(emu);

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

void sub(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(emu) : *get_lower_r8(emu);

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

void sbc(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(emu) : *get_lower_r8(emu);

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

void and_(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(emu) : *get_lower_r8(emu);

  const uint8_t result = cpu->registers.a & value;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG);
  SET_FLAG(cpu, HALFCARRY_FLAG);
  CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.a = (uint8_t)result;
}

void or_(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(emu) : *get_lower_r8(emu);

  const uint8_t result = cpu->registers.a | value;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

  cpu->registers.a = (uint8_t)result;
}

void xor_(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(emu) : *get_lower_r8(emu);

  const uint8_t result = cpu->registers.a ^ value;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

  cpu->registers.a = (uint8_t)result;
}

void cp(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const uint8_t value =
      cpu->opcode & 0x40 ? get_imm8(emu) : *get_lower_r8(emu);

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

void inc(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t *reg = get_middle_r8(emu);
	const uint8_t result = *reg + 1;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  CLEAR_FLAG(cpu, NEGATIVE_FLAG);

  const uint8_t half_carry = (*reg & 0x0F) + 1 > 0x0F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  *reg = result;
}

void dec(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  uint8_t *reg = get_middle_r8(emu);
	const uint8_t result = *reg - 1;

  if(result) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);

  SET_FLAG(cpu, NEGATIVE_FLAG);

  const uint8_t half_carry = (*reg & 0x0F) == 0x00;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  *reg = result;
}

// 16-bit arithmetic
void addhl(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
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

void addsp(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const uint8_t value   = get_imm8(emu);
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

void inc16(const emu_t *emu) { (*get_r16(emu->cpu))++; }

void dec16(const emu_t *emu) { (*get_r16(emu->cpu))--; }
