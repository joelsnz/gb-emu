#include "registers.h"
#include "memory.h"
#include "flags.h"

#include "miscellaneous.h"

void swap(uint8_t *reg) {
	uint8_t result = (*reg << 4) | (*reg >> 4);

	if(result) CLEAR_FLAG(ZERO_FLAG);
	else SET_FLAG(ZERO_FLAG);

	CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

	*reg = result;
}

void daa(void) {
	uint16_t result = registers.a;

	if((result & 0x0F) > 0x09) result += 0x06;
	if((result & 0xF0) > 0x90) result += 0x60;

	if(result) CLEAR_FLAG(ZERO_FLAG);
	else SET_FLAG(ZERO_FLAG);

	CLEAR_FLAG(HALFCARRY_FLAG);

	if(result > UINT16_MAX) SET_FLAG(CARRY_FLAG);
	else CLEAR_FLAG(CARRY_FLAG);

	registers.a = result;
}

void cpl(void) {
	SET_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG);

	registers.a = ~registers.a;
}

void ccf(void) {
	CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG);

	if(ISSET_FLAG(CARRY_FLAG)) CLEAR_FLAG(CARRY_FLAG);
	else SET_FLAG(CARRY_FLAG);
}

void scf(void) {
	CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG);

	SET_FLAG(CARRY_FLAG);
}

void nop(void) {;}