#include "instructions/call.h"

#include "cpu.h"
#include "mmu.h"
#include "instructions/miscellaneous.h"

#include <stdint.h>

void call(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  uint16_t *sp = &cpu->registers.sp;
  const uint16_t ret_addr = cpu->registers.pc + 0x03; // after imm16

  mmu->raw[--(*sp)] = (ret_addr >> 8) & 0xFF;
  mmu->raw[--(*sp)] = ret_addr & 0xFF;

  cpu->registers.pc = get_imm16(emu);
}

void callc(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  if(get_cond(cpu)) call(emu);
}

void rst(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  uint16_t *sp = &cpu->registers.sp;
  const uint16_t ret_addr = cpu->registers.pc;

  mmu->raw[--(*sp)] = (ret_addr >> 8) & 0xFF;
  mmu->raw[--(*sp)] = ret_addr & 0xFF;

  cpu->registers.pc = (uint16_t)get_tgt3(cpu) & 0x00FF;
}

void ret(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  const mmu_t *mmu = emu->mmu;
  uint16_t *sp = &cpu->registers.sp;

  const uint8_t pcl = mmu->raw[(*sp)++];
  const uint8_t pch = mmu->raw[(*sp)++];

  cpu->registers.pc = ((uint16_t)pch << 8) | pcl;
}

void retc(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  if(get_cond(cpu)) ret(emu);
}

void reti(const emu_t *emu) {
  ret(emu);
  ei(emu);
}
