#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "registers.h"

typedef struct {
	registers_t registers;
	uint8_t *r8;
	uint8_t memory[0xFFFF + 1];
} cpu_t;

void init_cpu(cpu_t *cpu);

#endif //CPU_H