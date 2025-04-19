#ifndef SHIFTS_H
#define SHIFTS_H

#include <stdint.h>

void rlca(cpu_t *cpu);
void rla(cpu_t *cpu);
void rrca(cpu_t *cpu);
void rra(cpu_t *cpu);
void rlc(cpu_t *cpu);
void rl(cpu_t *cpu);
void rrc(cpu_t *cpu);
void rr(cpu_t *cpu);
void sla(cpu_t *cpu);
void sra(cpu_t *cpu);
void srl(cpu_t *cpu);

#endif //SHIFTS_H
