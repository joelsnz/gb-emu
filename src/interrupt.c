#include "interrupt.h"

#include <stdint.h>

void push_pc(cpu_t *cpu) {
  uint16_t *sp = &cpu->registers.sp;
  uint16_t *pc = &cpu->registers.pc;

  cpu->memory.raw[--(*sp)] = (*pc >> 8) & 0xFF;
  cpu->memory.raw[--(*sp)] = (*pc) & 0xFF;
}

void handle_interrupt(cpu_t *cpu) {
  uint8_t *ie = &cpu->memory.ie;
  uint8_t *if_ = &cpu->memory.if_;
  uint8_t pending_interrupts = *ie & *if_;

  for(int i = 0; i <= 4 && cpu->ime; i++) {
    if(pending_interrupts & (1 << i)) {
      cpu->ime = 0;
      *if_ &= ~(1 << i);

      push_pc(cpu);

      cpu->registers.pc = 0x40 + (0x08 * i);
      cpu->cycles += 5;

      break; // only one interrupt per cycle
    }
  }
}
