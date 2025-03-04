#include "registers.h"

#include "cpu.h"

#include <stdint.h>

// 8-bit arithmetic
void add(const uint8_t value) {
  uint16_t result = registers.a + value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG);

  uint8_t half_carry = (registers.a & 0x0F) + (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);
}
