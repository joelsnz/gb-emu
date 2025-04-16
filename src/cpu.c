#include "cpu.h"

void init_cpu(cpu_t *cpu) {
	init_r8(&cpu->registers, &cpu->r8);
}