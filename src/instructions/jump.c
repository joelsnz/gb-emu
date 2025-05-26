#include "instructions/jump.h"

#include "cpu.h"

void jp(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  cpu->registers.pc = get_imm16(emu);
}

void jpc(const emu_t *emu) {
  const cpu_t *cpu = emu->cpu;
  if(get_cond(cpu)) jp(emu);
}

void jphl(const emu_t *emu) {
  registers_t *registers = &emu->cpu->registers;
  registers->pc = registers->hl;
}

void jr(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  cpu->registers.pc += ((int8_t)get_imm8(emu) + 2);
}

void jrc(const emu_t *emu) {
  const cpu_t *cpu = emu->cpu;
  if(get_cond(cpu)) jr(emu);
}
