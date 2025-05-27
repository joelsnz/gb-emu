#include "interrupt.h"

#include "cpu.h"
#include "mmu.h"

#include <stdint.h>

void push_pc(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  uint16_t *sp = &cpu->registers.sp;
  const uint16_t *pc = &cpu->registers.pc;

  mmu->raw[--(*sp)] = (*pc >> 8) & 0xFF;
  mmu->raw[--(*sp)] = (*pc) & 0xFF;
}

void handle_interrupt(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  mmu_t *mmu = emu->mmu;
  const uint8_t *ie = &mmu->ie;
  uint8_t *if_ = &mmu->if_;
  const uint8_t pending_interrupts = *ie & *if_;

  for(int i = 0; i <= 4 && cpu->ime; i++) {
    if(pending_interrupts & (1 << i)) {
      cpu->ime = 0;
      *if_ &= ~(1 << i);

      push_pc(emu);

      cpu->registers.pc = 0x40 + (0x08 * i);
      cpu->cycles += 5;

      break; // only one interrupt per cycle
    }
  }
}
