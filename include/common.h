#ifndef COMMON_H
#define COMMON_H

#include "emulator.h"
#include <stdint.h>

void push_to_stack(const emu_t *emu, const uint16_t value);
uint16_t pop_from_stack(const emu_t *emu);

#endif //COMMON_H
