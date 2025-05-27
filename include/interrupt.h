#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "emulator.h"

void push_pc(const emu_t *emu);
void handle_interrupt(const emu_t *emu);

#endif // INTERRPUT_H
