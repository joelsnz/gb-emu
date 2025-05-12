#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>
#include "cpu.h"

#define VBLANK (1 << 0)
#define LCD	(1 << 1)
#define TIMER	(1 << 2)
#define SERIAL (1 << 3)
#define JOYPAD (1 << 4)

#define ISSET_BIT(reg, bit) ((reg & (bit)) != 0)
#define CLEAR_BIT(reg, bit) ((reg) &= ~(bit))

void handle_interrupts(cpu_t* cpu);

void handle_vblank(cpu_t* cpu);
void handle_lcd(cpu_t* cpu);
void handle_timer(cpu_t* cpu);
void handle_serial(cpu_t* cpu);
void handle_joypad(cpu_t* cpu);

#endif // INTERRPUT_H
