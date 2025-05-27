#include "instructions/bit.h"

#include "flags.h"
#include "cpu.h"

void bit(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const uint8_t index = get_b3(cpu);
  const uint8_t *reg = get_lower_r8(emu);

  if(*reg & 1 << index) CLEAR_FLAG(cpu, ZERO_FLAG);
  else SET_FLAG(cpu, ZERO_FLAG);
}

void set(const emu_t *emu) {
  const cpu_t *cpu = emu->cpu;
  const uint8_t index = get_b3(cpu);
  uint8_t *reg = get_lower_r8(emu);

  if(index) *reg |= (1 << index - 1);
}

void res(const emu_t *emu) {
  const cpu_t *cpu = emu->cpu;
  const uint8_t index = get_b3(cpu);
  uint8_t *reg = get_lower_r8(emu);

  if(index) *reg &= ~(1 << index - 1);
}
