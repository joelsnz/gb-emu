#include "cpu.h"

#include "common.h"
#include "flags.h"
#include "instructions/instructions.h"
#include "mmu.h"

void init_cpu(cpu_t *cpu) {
  cpu->cycles = 0;
  init_r8(&cpu->registers, cpu->r8);
  init_r16(&cpu->registers, cpu->r16);
  init_r16mem(&cpu->registers, cpu->r16mem);
  init_r16stk(&cpu->registers, cpu->r16stk);
  init_instr_list(cpu);
}

void get_opcode(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  cpu->opcode = mmu->raw[cpu->registers.pc];
}

void cpu_step(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  get_opcode(emu);
  uint16_t actual_pc = cpu->registers.pc;
  instruction_t instr = base_instr_list[cpu->opcode];

  if(cpu->opcode == 0xcb) { // prefixed instruction
    instr = prefix_instr_list[++cpu->opcode];
  }
  instr.instruction(emu);

  if(actual_pc ==
     cpu->registers.pc) // keep pc if some instr already modified it
    cpu->registers.pc += instr.bytes;

  cpu->cycles += instr.cycles;
}

uint8_t *get_lower_r8(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  const uint8_t reg = cpu->opcode & 0x07;

  return reg == 0x06 // r8 value
             ? &mmu->raw[cpu->registers.hl]
             : cpu->r8[reg];
}

uint8_t *get_middle_r8(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  const uint8_t reg = (cpu->opcode & 0x38) >> 3;

  return reg == 0x06 // r8 value
             ? &mmu->raw[cpu->registers.hl]
             : cpu->r8[reg];
}

uint8_t get_imm8(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  return mmu->raw[cpu->registers.pc + 1];
}

uint16_t get_imm16(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  return (mmu->raw[cpu->registers.pc + 2] << 8) | get_imm8(emu);
}

uint16_t *get_r16(const cpu_t *cpu) {
  const uint16_t reg = (cpu->opcode & 0x30) >> 4;
  return cpu->r16[reg];
}

uint16_t get_r16mem(cpu_t *cpu) {
  const uint16_t i = (cpu->opcode & 0x30) >> 4;
  const uint16_t reg = *cpu->r16mem[i];
  if(i == 2) cpu->registers.hl++;
  if(i == 3) cpu->registers.hl--;
  return reg;
}

uint16_t *get_r16stk(const cpu_t *cpu) {
  const uint16_t reg = (cpu->opcode & 0x30) >> 4;
  return cpu->r16stk[reg];
}

uint8_t get_tgt3(const cpu_t *cpu) {
  const uint8_t target = (cpu->opcode & 0x38) >> 3;
  return target * 0x08;
}

uint8_t get_b3(const cpu_t *cpu) { return (cpu->opcode & 0x38) >> 3; }

uint8_t get_cond(const cpu_t *cpu) {
  enum conditions_t { nz, z, nc, c };

  enum conditions_t cond =
      (enum conditions_t)(cpu->opcode & 0x18) >> 3;

  switch(cond) {
  case nz:
    return !ISSET_BIT(cpu->registers.f, ZERO_FLAG);
  case z:
    return ISSET_BIT(cpu->registers.f, ZERO_FLAG);
  case nc:
    return !ISSET_BIT(cpu->registers.f, CARRY_FLAG);
  case c:
    return ISSET_BIT(cpu->registers.f, CARRY_FLAG);
  default:
    return 0;
  }
}
