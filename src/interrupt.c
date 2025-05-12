#include "interrupt.h"

void handle_interrupts(cpu_t *cpu) {
  if(cpu->ime) {
    cpu->ime = 0;

    uint8_t *ie = &cpu->memory.ie;
    uint8_t *if = &cpu->memory.if;
    uint8_t pending_interrupts = *ie & *if;

    if(!pending_interrupts) return;

    if(pending_interrupts & VBLANK) {
      *if &= ~VBLANK;
      handle_vblank();
    }

    if(pending_interrupts & LCD) {
      *if &= ~LCD;
      handle_lcd();
    }

    if(pending_interrupts & TIMER) {
      *if &= ~TIMER;
      handle_timer();
    }

    if(pending_interrupts & SERIAL) {
      *if &= ~SERIAL;
      handle_serial();
    }

    if(pending_interrupts & JOYPAD) {
      *if &= ~JOYPAD;
      handle_joypad();
    }
  }
}
