#include "common.h"

#include "mmu.h"
#include "cpu.h"

void push_to_stack(const emu_t *emu, const uint16_t value) {
  mmu_t *mmu = emu->mmu;
  uint16_t *sp = &emu->cpu->registers.sp;

  mmu->raw[--(*sp)] = (value >> 8) & 0xFF;
  mmu->raw[--(*sp)] = value & 0xFF;
}

uint16_t pop_from_stack(const emu_t *emu) {
  const mmu_t *mmu = emu->mmu;
  uint16_t *sp = &emu->cpu->registers.sp;

  const uint8_t pcl = mmu->raw[(*sp)++];
  const uint8_t pch = mmu->raw[(*sp)++];

  return ((uint16_t)pch << 8) | pcl;
}