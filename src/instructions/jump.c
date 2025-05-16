#include "instructions/jump.h"

void jp(cpu_t *cpu) { cpu->registers.pc = get_imm16(cpu); }

void jpc(cpu_t *cpu) {
  if(get_cond(cpu)) jp(cpu);
}
void jphl(cpu_t *cpu) { cpu->registers.pc = cpu->registers.hl; }

void jr(cpu_t *cpu) { cpu->registers.pc += ((int8_t)get_imm8(cpu) + 2); }

void jrc(cpu_t *cpu) {
  if(get_cond(cpu)) jr(cpu);
}
