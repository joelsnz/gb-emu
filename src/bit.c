#include "bit.h"

#include "flags.h"

void bit(cpu_t *cpu) {
  uint8_t index = get_b3(cpu);
  uint8_t *reg = get_lower_r8(cpu);

  if(*reg & 1 << index) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);
}

void set(cpu_t *cpu) {
  uint8_t index = get_b3(cpu);
  uint8_t *reg = get_lower_r8(cpu);

  if(index) *reg |= (1 << index - 1);
}

void res(cpu_t *cpu) {
  uint8_t index = get_b3(cpu);
  uint8_t *reg = get_lower_r8(cpu);

  if(index) *reg &= ~(1 << index - 1);
}
