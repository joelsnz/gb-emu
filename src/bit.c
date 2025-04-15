#include "registers.h"
#include "memory.h"
#include "flags.h"

#include "bit.h"

void bit(uint8_t index, uint8_t *reg) {
	if(*reg & 1 << index) CLEAR_FLAG(ZERO_FLAG);
	else SET_FLAG(ZERO_FLAG);
}

void set(uint8_t index, uint8_t *reg) {
	*reg |= 1 << index;
}

void res(uint8_t index, uint8_t *reg) {
	*reg &= ~(1 << index);
}