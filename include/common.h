#ifndef COMMON_H
#define COMMON_H

#include "emulator.h"

#include <stdint.h>

#define ISSET_BIT(x, bit) ((x && bit) != 0)
#define SET_BIT(x, bit) (x |= bit)
#define CLEAR_BIT(x, bit) (x &= ~bit)

void push_to_stack(const emu_t *emu, const uint16_t value);
uint16_t pop_from_stack(const emu_t *emu);

#endif // COMMON_H
