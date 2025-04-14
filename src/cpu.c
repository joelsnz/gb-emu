#include "cpu.h"

#include <stdio.h>

#include "instructions.h"
#include "memory.h"
#include "registers.h"

// impl: sub sbc and or xor cp inc dec
// impl: 16-bit arithmetic
// impl: miscellaneous
// impl: rotates & shifts
// impl: bit opcodes

int prefix_execute(const uint8_t opcode) {
	switch(opcode) {
		case 0x00: rlc(&registers.b); break;
		case 0x01: rlc(&registers.c); break;
		case 0x02: rlc(&registers.d); break;
		case 0x03: rlc(&registers.e); break;
		case 0x04: rlc(&registers.h); break;
		case 0x05: rlc(&registers.l); break;
		case 0x06: rlc(&memory[registers.hl]); break;
		case 0x07: rlc(&registers.a); break;

		default: return registers.pc;
	}
	return registers.pc++;
}

int execute(const uint8_t opcode) {
	switch(opcode) {
		case 0x00: nop(); break;
		case 0x80: add(registers.b); break;
		case 0x81: add(registers.c); break;
		case 0x82: add(registers.d); break;
		case 0x83: add(registers.e); break;
		case 0x84: add(registers.h); break;
		case 0x85: add(registers.l); break;
		case 0x86: add(memory[registers.hl]); break;
		case 0x87: add(registers.a); break;
		case 0x88: adc(registers.b); break;
		case 0x89: adc(registers.c); break;
		case 0x8a: adc(registers.d); break;
		case 0x8b: adc(registers.e); break;
		case 0x8c: adc(registers.h); break;
		case 0x8d: adc(registers.l); break;
		case 0x8e: adc(memory[registers.hl]); break;
		case 0x8f: adc(registers.a); break;
		case 0x90: sub(registers.b); break;
		case 0x91: sub(registers.c); break;
		case 0x92: sub(registers.d); break;
		case 0x93: sub(registers.e); break;
		case 0x94: sub(registers.h); break;
		case 0x95: sub(registers.l); break;
		case 0x96: sub(memory[registers.hl]); break;
		case 0x97: sub(registers.a); break;
		case 0x98: sbc(registers.b); break;
		case 0x99: sbc(registers.c); break;
		case 0x9a: sbc(registers.d); break;
		case 0x9b: sbc(registers.e); break;
		case 0x9c: sbc(registers.h); break;
		case 0x9d: sbc(registers.l); break;
		case 0x9e: sbc(memory[registers.hl]); break;
		case 0x9f: sbc(registers.a); break;
		case 0xa0: and(registers.b); break;
		case 0xa1: and(registers.c); break;
		case 0xa2: and(registers.d); break;
		case 0xa3: and(registers.e); break;
		case 0xa4: and(registers.h); break;
		case 0xa5: and(registers.l); break;
		case 0xa6: and(memory[registers.hl]); break;
		case 0xa7: and(registers.a); break;
		case 0xa8: xor(registers.b); break;
		case 0xa9: xor(registers.c); break;
		case 0xaa: xor(registers.d); break;
		case 0xab: xor(registers.e); break;
		case 0xac: xor(registers.h); break;
		case 0xad: xor(registers.l); break;
		case 0xae: xor(memory[registers.hl]); break;
		case 0xaf: xor(registers.a); break;
		case 0xb0: or(registers.b); break;
		case 0xb1: or(registers.c); break;
		case 0xb2: or(registers.d); break;
		case 0xb3: or(registers.e); break;
		case 0xb4: or(registers.h); break;
		case 0xb5: or(registers.l); break;
		case 0xb6: or(memory[registers.hl]); break;
		case 0xb7: or(registers.a); break;
		case 0xb8: cp(registers.b); break;
		case 0xb9: cp(registers.c); break;
		case 0xba: cp(registers.d); break;
		case 0xbb: cp(registers.e); break;
		case 0xbc: cp(registers.h); break;
		case 0xbd: cp(registers.l); break;
		case 0xbe: cp(memory[registers.hl]); break;
		case 0xbf: cp(registers.a); break;
		default: return registers.pc;
	}
	return registers.pc++;
}

void step() {
	uint16_t next_pc = memory[registers.pc] == 0xCB
	? prefix_execute(memory[++registers.pc])
	: execute(memory[registers.pc]);

	if(next_pc == registers.pc)
		printf("failed to execute\n");
}
