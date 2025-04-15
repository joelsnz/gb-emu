#include "registers.h"
#include "memory.h"
#include "flags.h"

#include "arithmetic.h"

// 8-bit ALU
void add(const uint8_t value) {
  const uint16_t result = registers.a + value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry =
    (registers.a & 0x0F) + (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void adc(const uint8_t value) {
  const uint16_t result =
    registers.a + value + ISSET_FLAG(CARRY_FLAG);

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry =
    (registers.a & 0x0F) + (value & 0x0F) + ISSET_FLAG(CARRY_FLAG) > 0x0F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void sub(const uint8_t value) {
  const uint16_t result = registers.a - value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  SET_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry = (registers.a & 0x0F) - (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void sbc(const uint8_t value) {
  const uint16_t result = registers.a - value - ISSET_FLAG(CARRY_FLAG);

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  SET_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry =
    (registers.a & 0x0F) - (value & 0x0F) - ISSET_FLAG(CARRY_FLAG) > 0x0F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void and(const uint8_t value) {
  const uint8_t result = registers.a & value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG);
  SET_FLAG(HALFCARRY_FLAG);
  CLEAR_FLAG(CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void or(const uint8_t value) {
  const uint8_t result = registers.a | value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void xor(const uint8_t value) {
  const uint8_t result = registers.a ^ value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void cp(const uint8_t value) {
  const uint16_t result = registers.a - value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  SET_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry = (registers.a & 0x0F) - (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);
}

void inc(const uint8_t *reg) {
  if(*reg) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry = (*reg & 0x0F) == 0x0F;
  if(half_carry) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  *reg++;
}

void dec(const uint8_t *reg) {
  if(*reg) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  SET_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry = (*reg & 0x0F) == 0x00;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  *reg--;
}

// 16-bit arithmetic
void addhl(const uint16_t value) {
  uint32_t result = registers.hl + value;

  CLEAR_FLAG(NEGATIVE_FLAG);

  const uint16_t half_carry =
    (registers.hl & 0x000F) + (value & 0x000F) > 0x000F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT16_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  registers.hl = result;
}

void addsp(const int8_t value) {
  uint32_t result = registers.sp + value;

  CLEAR_FLAG(ZERO_FLAG | NEGATIVE_FLAG);

  const uint16_t half_carry =
    (registers.sp & 0x000F) + (value & 0x000F) > 0x000F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT16_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  registers.sp = result;
}

void inc16(const uint16_t *reg) {
  *reg++;
}

void dec16(const uint16_t *reg) {
  *reg--;
}