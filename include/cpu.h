#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "registers.h"

typedef struct {
	registers_t registers;
	uint8_t *r8[8];
	uint16_t *r16[4];
	uint8_t memory[0xFFFF + 1];
	uint8_t opcode;
} cpu_t;

void init_cpu(cpu_t *cpu);
void get_opcode(cpu_t *cpu);

#endif //CPU_H