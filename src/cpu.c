#include "registers.h"
#include "flags.h"

#include "cpu.h"

// 8-bit arithmetic
void add(const uint8_t value) {
  const uint16_t result = registers.a + value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry =
    (registers.a & 0x0F) + (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

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
  if(half_carry) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  registers.a = (uint8_t) result;
}

void sub(const uint8_t value) {
  const uint16_t result = registers.a - value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  SET_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry = (registers.a & 0x0F) - (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

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

void xor(const uint8_t value) {
  const uint8_t result = registers.a ^ value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG);
  CLEAR_FLAG(HALFCARRY_FLAG);
  CLEAR_FLAG(CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void or(const uint8_t value) {
  const uint8_t result = registers.a | value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG);
  CLEAR_FLAG(HALFCARRY_FLAG);
  CLEAR_FLAG(CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void cp(const uint8_t value) {
  const uint16_t result = registers.a - value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  SET_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry = (registers.a & 0x0F) - (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);
}