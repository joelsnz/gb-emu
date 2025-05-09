#ifndef CALL_H
#define CALL_H

#include "cpu.h"

void call(cpu_t *cpu);
void callc(cpu_t *cpu);

void rst(cpu_t *cpu);

void ret(cpu_t *cpu);
void retc(cpu_t *cpu);
void reti(cpu_t *cpu);

#endif // CALL_H
