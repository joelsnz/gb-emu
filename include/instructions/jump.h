#ifndef JUMP_H
#define JUMP_H

#include "cpu.h"

void jp(cpu_t *cpu);
void jpc(cpu_t *cpu);
void jphl(cpu_t *cpu);
void jr(cpu_t *cpu);
void jrc(cpu_t *cpu);

#endif // JUMP_H
