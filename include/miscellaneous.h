#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include "cpu.h"

void swap(cpu_t *cpu);
void daa(cpu_t *cpu);
void cpl(cpu_t *cpu);
void ccf(cpu_t *cpu);
void scf(cpu_t *cpu);
void nop(cpu_t *cpu);
void halt(cpu_t *cpu); // tbi
void stop(cpu_t *cpu); // tbi
void di(cpu_t *cpu); // tbi
void ei(cpu_t *cpu); // tbi

#endif //MISCELLANEOUS_H
