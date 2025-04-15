#include "registers.h"
#include "memory.h"
#include "flags.h"

#include "instructions.h"

// 8-bit ALU
void add(const uint8_t value) {
  const uint16_t result = registers.a + value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry =
    (registers.a & 0x0F) + (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void adc(const uint8_t value) {
  const uint16_t result =
    registers.a + value + ISSET_FLAG(CARRY_FLAG);

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry =
    (registers.a & 0x0F) + (value & 0x0F) + ISSET_FLAG(CARRY_FLAG) > 0x0F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void sub(const uint8_t value) {
  const uint16_t result = registers.a - value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  SET_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry = (registers.a & 0x0F) - (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void sbc(const uint8_t value) {
  const uint16_t result = registers.a - value - ISSET_FLAG(CARRY_FLAG);

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  SET_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry =
    (registers.a & 0x0F) - (value & 0x0F) - ISSET_FLAG(CARRY_FLAG) > 0x0F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void and(const uint8_t value) {
  const uint8_t result = registers.a & value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG);
  SET_FLAG(HALFCARRY_FLAG);
  CLEAR_FLAG(CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void or(const uint8_t value) {
  const uint8_t result = registers.a | value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void xor(const uint8_t value) {
  const uint8_t result = registers.a ^ value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG | HALFCARRY_FLAG | CARRY_FLAG);

  registers.a = (uint8_t) result;
}

void cp(const uint8_t value) {
  const uint16_t result = registers.a - value;

  if(result) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  SET_FLAG(NEGATIVE_FLAG);

  const uint8_t half_carry = (registers.a & 0x0F) - (value & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);
}

void inc(const uint8_t *reg) {
  if(*reg) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  CLEAR_FLAG(NEGATIVE_FLAG);
  
  const uint8_t half_carry = (*reg & 0x0F) == 0x0F;
  if(half_carry) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);
  
  *reg++;
}

void dec(const uint8_t *reg) {
  if(*reg) CLEAR_FLAG(ZERO_FLAG);
  else SET_FLAG(ZERO_FLAG);

  SET_FLAG(NEGATIVE_FLAG);
  
  const uint8_t half_carry = (*reg & 0x0F) == 0x00;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);
  
  *reg--;
}

// 16-bit arithmetic
void addhl(const uint16_t value) {
  uint32_t result = registers.hl + value;
  
  CLEAR_FLAG(NEGATIVE_FLAG);

  const uint16_t half_carry =
    (registers.hl & 0x000F) + (value & 0x000F) > 0x000F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT16_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);
  
  registers.hl = result;
}

void addsp(const int8_t value) {
  uint32_t result = registers.sp + value;

  CLEAR_FLAG(ZERO_FLAG | NEGATIVE_FLAG);
  
  const uint16_t half_carry =
    (registers.sp & 0x000F) + (value & 0x000F) > 0x000F;
  if(half_carry) SET_FLAG(HALFCARRY_FLAG);
  else CLEAR_FLAG(HALFCARRY_FLAG);

  if(result > UINT16_MAX) SET_FLAG(CARRY_FLAG);
  else CLEAR_FLAG(CARRY_FLAG);
  
  registers.sp = result;
}

void inc16(const uint16_t *reg) {
  *reg++;
}

void dec16(const uint16_t *reg) {
  *reg--;
}

// miscellaneous
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

// rotates & shifts
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

// bit opcodes
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
