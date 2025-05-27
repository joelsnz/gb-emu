#include "instructions/load.h"

#include "flags.h"
#include "cpu.h"
#include "mmu.h"
#include "common.h"

void ld(const emu_t *emu) {
  uint8_t *dest = get_middle_r8(emu);
  const uint8_t *source = get_lower_r8(emu);

  *dest = *source;
}

void ldi(const emu_t *emu) {
  uint8_t *dest = get_middle_r8(emu);
  const uint8_t imm = get_imm8(emu);

  *dest = imm;
}

void lda(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const mmu_t *mmu = emu->mmu;
  const uint16_t source = get_r16mem(cpu);

  cpu->registers.a = mmu->raw[source];
}

void ldfa(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  const uint16_t dest = get_r16mem(cpu);

  mmu->raw[dest] = cpu->registers.a;
}

void ldad(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const mmu_t *mmu = emu->mmu;
  const uint16_t addr = get_imm16(emu);

  cpu->registers.a = mmu->raw[addr];
}

void ldfad(const emu_t *emu) {
  const cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  const uint16_t addr = get_imm16(emu);

  mmu->raw[addr] = cpu->registers.a;
}

void ldh(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const mmu_t *mmu = emu->mmu;
  const uint16_t addr = cpu->registers.c + 0xff00;

  cpu->registers.a = mmu->raw[addr];
}

void ldhf(const emu_t *emu) {
  const cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  const uint16_t addr = cpu->registers.c + 0xff00;

  mmu->raw[addr] = cpu->registers.a;
}

void ldhi(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const mmu_t *mmu = emu->mmu;
  const uint8_t imm = get_imm8(emu);
  const uint16_t addr = imm + 0xff00;

  cpu->registers.a = mmu->raw[addr];
}

void ldhfi(const emu_t *emu) {
  const cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  const uint8_t imm = get_imm8(emu);
  const uint16_t addr = imm + 0xff00;

  mmu->raw[addr] = cpu->registers.a;
}

void ldi16(const emu_t *emu) {
  const cpu_t *cpu = emu->cpu;
  uint16_t *dest = get_r16(cpu);
  const uint16_t imm = get_imm16(emu);

  *dest = imm;
}

void ldsp(const emu_t *emu) {
  const cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  const uint16_t addr = get_imm16(emu);

  mmu->raw[addr] = cpu->registers.sp;
}

void ldsphl(const emu_t *emu) {
  registers_t *registers = &emu->cpu->registers;
  registers->sp = registers->hl;
}

void ldhlsp(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const uint8_t imm = get_imm8(emu);
  const uint16_t result = cpu->registers.sp + imm;

  CLEAR_FLAG(cpu, ZERO_FLAG | NEGATIVE_FLAG);

  const uint8_t half_carry =
      (cpu->registers.sp & 0x0F) + (imm & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.hl = result;
}

void push(const emu_t *emu) {
  const uint16_t *reg = get_r16stk(emu->cpu);

  push_to_stack(emu, *reg);
}

void pop(const emu_t *emu) {
  const cpu_t *cpu = emu->cpu;

  uint16_t *reg = get_r16stk(cpu);

  *reg = pop_from_stack(emu);

  if(reg == &cpu->registers.af)
    *reg &= 0xfff0; // f's lsb must be blank
}
