#include "jump.h"

void jp(cpu_t *cpu) { cpu->registers.pc = get_imm16(cpu); }

void jpc(cpu_t *cpu) {
  if(get_cond(cpu)) cpu->registers.pc = get_imm16(cpu);
}
void jphl(cpu_t *cpu) { cpu->registers.pc = cpu->registers.hl; }

void jr(cpu_t *cpu) { cpu->registers.pc += get_imm8(cpu); }

void jrc(cpu_t *cpu) {
  if(get_cond(cpu)) cpu->registers.pc += get_imm8(cpu);
}
