#include "cpu.h"

#include "flags.h"
#include "instructions.h"

void init_cpu(cpu_t *cpu) {
  init_r8(&cpu->registers, cpu->r8);
  init_r16(&cpu->registers, cpu->r16);
  init_r16mem(&cpu->registers, cpu->r16mem);
  init_r16stk(&cpu->registers, cpu->r16stk);
  init_instr_list(cpu);
}

void get_opcode(cpu_t *cpu) {
  cpu->opcode = cpu->memory.raw[cpu->registers.pc];
}

void get_next_opcode(cpu_t *cpu) {
  cpu->opcode = cpu->memory.raw[cpu->registers.pc + 1];
}

void step(cpu_t *cpu) {
  get_opcode(cpu);
  uint16_t actual_pc = cpu->registers.pc;
  instruction_t instr = base_instr_list[cpu->opcode];
  if(cpu->opcode == 0xcb) { // prefixed instruction
    get_next_opcode(cpu);
    instr = prefix_instr_list[cpu->opcode];
  }
  instr.instruction(cpu);
  if(actual_pc ==
     cpu->registers.pc) // keep pc if some instr already modified it
    cpu->registers.pc += instr.bytes;
}

uint8_t *get_lower_r8(cpu_t *cpu) {
  const uint8_t reg = cpu->opcode & 0x07;

  return reg == 0x06 // r8 value
             ? &cpu->memory.raw[cpu->registers.hl]
             : cpu->r8[reg];
}

uint8_t *get_middle_r8(cpu_t *cpu) {
  const uint8_t reg = (cpu->opcode & 0x38) >> 3;

  return reg == 0x06 // r8 value
             ? &cpu->memory.raw[cpu->registers.hl]
             : cpu->r8[reg];
}

uint8_t get_imm8(cpu_t *cpu) {
  return cpu->memory.raw[cpu->registers.pc + 1];
}

uint16_t get_imm16(cpu_t *cpu) {
  return (cpu->memory.raw[cpu->registers.pc + 2] << 8) | get_imm8(cpu);
}

uint16_t *get_r16(cpu_t *cpu) {
  const uint16_t reg = (cpu->opcode & 0x30) >> 4;
  return cpu->r16[reg];
}

uint16_t *get_r16mem(cpu_t *cpu) {
  const uint16_t i = (cpu->opcode & 0x30) >> 4;
  uint16_t *reg = cpu->r16mem[i];
  if(i == 2) cpu->registers.hl++;
  if(i == 3) cpu->registers.hl--;
  return reg;
}

uint16_t *get_r16stk(cpu_t *cpu) {
  const uint16_t reg = (cpu->opcode & 0x30) >> 4;
  return cpu->r16stk[reg];
}

uint8_t get_tgt3(cpu_t *cpu) {
  const uint8_t target = (cpu->opcode & 0x38) >> 3;
  return target * 0x08;
}

uint8_t get_b3(cpu_t *cpu) { return (cpu->opcode & 0x38) >> 3; }

uint8_t get_cond(cpu_t *cpu) {
  enum conditions_t { nz, z, nc, c };

  enum conditions_t cond =
      (enum conditions_t)(cpu->opcode & 0x18) >> 3;

  switch(cond) {
  case nz:
    return !ISSET_FLAG(cpu, ZERO_FLAG);
  case z:
    return ISSET_FLAG(cpu, ZERO_FLAG);
  case nc:
    return !ISSET_FLAG(cpu, CARRY_FLAG);
  case c:
    return ISSET_FLAG(cpu, CARRY_FLAG);
  default:
    return 0;
  }
}