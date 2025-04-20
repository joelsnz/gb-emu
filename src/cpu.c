#include "cpu.h"

#include "instructions.h"

void init_cpu(cpu_t *cpu) {
  init_r8(&cpu->registers, cpu->r8);
  init_r16(&cpu->registers, cpu->r16);
  init_instr_list();
}

void get_opcode(cpu_t *cpu) {
  cpu->opcode = cpu->memory[cpu->registers.pc];
}

void step(cpu_t *cpu) {
  get_opcode(cpu);
  base_instr_list[cpu->opcode].instruction(cpu);
  cpu->registers.pc += base_instr_list[cpu->opcode].bytes;
}

uint8_t *get_lower_r8(cpu_t *cpu) {
  const uint8_t reg = cpu->opcode & 0x07;

  return reg == 0x06 // r8 value
             ? &cpu->memory[cpu->registers.hl]
             : cpu->r8[reg];
}

uint8_t *get_middle_r8(cpu_t *cpu) {
  const uint8_t reg = (cpu->opcode & 0x38) >> 3;

  return reg == 0x06 // r8 value
             ? &cpu->memory[cpu->registers.hl]
             : cpu->r8[reg];
}

uint8_t *get_imm8(cpu_t *cpu) {
  return &cpu->memory[cpu->registers.pc + 1];
}

uint16_t *get_r16(cpu_t *cpu) {
  const uint16_t reg = (cpu->opcode & 0x30) >> 4;
  return cpu->r16[reg];
}

uint8_t get_b3(cpu_t *cpu) { return (cpu->opcode & 0x38) >> 3; }
