#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "cpu.h"

void push_pc(cpu_t *cpu);
void handle_interrupt(cpu_t* cpu);

#endif // INTERRPUT_H
