#include "call.h"

#include "miscellaneous.h"

void call(cpu_t *cpu) {
  uint16_t *sp = &cpu->registers.sp;
  uint16_t ret_addr = cpu->registers.pc + 0x03; // after imm16

  cpu->memory.raw[--(*sp)] = (ret_addr >> 8) & 0xFF;
  cpu->memory.raw[--(*sp)] = ret_addr & 0xFF;

  cpu->registers.pc = get_imm16(cpu);
}

void callc(cpu_t *cpu) {
  if(get_cond(cpu)) call(cpu);
}

void rst(cpu_t *cpu) {
  uint16_t *sp = &cpu->registers.sp;
  uint16_t ret_addr = cpu->registers.pc;

  cpu->memory.raw[--(*sp)] = (ret_addr >> 8) & 0xFF;
  cpu->memory.raw[--(*sp)] = ret_addr & 0xFF;

  cpu->registers.pc = (uint16_t)get_tgt3(cpu) & 0x00FF;
}

void ret(cpu_t *cpu) {
  uint16_t *sp = &cpu->registers.sp;

  uint8_t pcl = cpu->memory.raw[(*sp)++];
  uint8_t pch = cpu->memory.raw[(*sp)++];

  cpu->registers.pc = ((uint16_t)pch << 8) | pcl;
}

void retc(cpu_t *cpu) {
  if(get_cond(cpu)) ret(cpu);
}

void reti(cpu_t *cpu) {
  ret(cpu);
  ei(cpu);
}
