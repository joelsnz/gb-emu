#include "cpu.h"

void init_cpu(cpu_t *cpu) {
	init_r8(&cpu->registers, cpu->r8);
	init_r16(&cpu->registers, cpu->r16);
}

void get_opcode(cpu_t *cpu) {
	cpu->opcode = cpu->memory[cpu->registers.pc];
}