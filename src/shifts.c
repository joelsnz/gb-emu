#include "registers.h"
#include "memory.h"
#include "flags.h"

#include "shifts.h"

void rlca(void) {
	uint8_t result = registers.a << 1;

	CLEAR_FLAG(ZERO_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);

	if(registers.a & 0x80) {
		SET_FLAG(CARRY_FLAG);
		result++;
	} else {
		CLEAR_FLAG(CARRY_FLAG);
	}

	registers.a = result;
}

void rla(void) {
	uint8_t result = registers.a << 1;

	result += ISSET_FLAG(CARRY_FLAG);

	CLEAR_FLAG(ZERO_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);

	if(registers.a & 0x80) SET_FLAG(CARRY_FLAG);
	else CLEAR_FLAG(CARRY_FLAG);

	registers.a = result;
}

void rrca(void) {
	uint8_t result = registers.a >> 1;

	CLEAR_FLAG(ZERO_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);

	if(registers.a & 0x01) {
		SET_FLAG(CARRY_FLAG);
		result |= 0x80;
	} else {
		CLEAR_FLAG(CARRY_FLAG);
	}

	registers.a = result;
}

void rra(void) {
	uint8_t result = registers.a >> 1;

	result += ISSET_FLAG(CARRY_FLAG) ? 0x80 : 0x00;

	CLEAR_FLAG(ZERO_FLAG | NEGATIVE_FLAG | HALFCARRY_FLAG);

	if(registers.a & 0x01) SET_FLAG(CARRY_FLAG);
	else CLEAR_FLAG(CARRY_FLAG);

	registers.a = result;
}

void rlc(uint8_t *reg) {
	uint8_t result = *reg << 1;

	CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG);

	if(*reg & 0x80) {
		SET_FLAG(CARRY_FLAG);
		result++;
	} else {
		CLEAR_FLAG(CARRY_FLAG);
	}

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

	*reg = result;
}

void rl(uint8_t *reg) {
	uint8_t result = *reg << 1;

	result += ISSET_FLAG(CARRY_FLAG);

	CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG);

	if(*reg & 0x80) SET_FLAG(CARRY_FLAG);
	else CLEAR_FLAG(CARRY_FLAG);

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

	*reg = result;
}

void rrc(uint8_t *reg) {
	uint8_t result = *reg >> 1;

	CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG);

	if(*reg & 0x01) {
		SET_FLAG(CARRY_FLAG);
		result |= 0x80;
	} else {
		CLEAR_FLAG(CARRY_FLAG);
	}

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

	*reg = result;
}

void rr(uint8_t *reg) {
	uint8_t result = *reg >> 1;

	result += ISSET_FLAG(CARRY_FLAG) ? 0x80 : 0x00;

	CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG);

	if(*reg & 0x01) SET_FLAG(CARRY_FLAG);
	else CLEAR_FLAG(CARRY_FLAG);

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

	*reg = result;
}

void sla(uint8_t *reg) {
  uint8_t result = *reg << 1;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

	CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x80) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  *reg = result;
}

void sra(uint8_t *reg) {
  uint8_t result = (*reg >> 1) | (*reg & 0x80);

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

	CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x01) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  *reg = result;
}

void srl(uint8_t *reg) {
  uint8_t result = *reg >> 1;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

	CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG);

  if(*reg & 0x01) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  *reg = result;
}