#ifndef CPU_H
#define CPU_H

#include <stdint.h>

// 8-bit arithmetic
void add(const uint8_t value);
void adc(const uint8_t value);
void sub(const uint8_t value);
void sbc(const uint8_t value);
void and(const uint8_t value);
void xor(const uint8_t value);
void or(const uint8_t value);
void cp(const uint8_t value);

#endif // CPU_H