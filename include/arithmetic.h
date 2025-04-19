#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <stdint.h>

#include "cpu.h"

// 8-bit arithmetic
void add(cpu_t *cpu);
void adc(cpu_t *cpu);
void sub(cpu_t *cpu);
void sbc(cpu_t *cpu);
void and_(cpu_t *cpu);
void or_(cpu_t *cpu);
void xor_(cpu_t *cpu);
void cp(cpu_t *cpu);
void inc(cpu_t *cpu);
void dec(cpu_t *cpu);

// 16-bit arithmetic
void addhl(cpu_t *cpu);
void addsp(cpu_t *cpu);
void inc16(cpu_t *cpu);
void dec16(cpu_t *cpu);

#endif //ARITHMETIC_H
