#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

#define ISSET_BIT(reg, bit) ((reg & (bit)) != 0)
#define SET_BIT(reg, bit) ((reg) |= (bit))
#define CLEAR_BIT(reg, bit) ((reg) &= ~(bit))

enum interrput_bit : uint8_t {
  VBLANK,
  LCD,
  TIMER,
  SERIAL,
  JOYPAD
};

#endif // INTERRPUT_H
