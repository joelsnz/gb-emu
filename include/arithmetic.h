#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <stdint.h>

// 8-bit arithmetic
void add(const uint8_t value);
void adc(const uint8_t value);
void sub(const uint8_t value);
void sbc(const uint8_t value);
void and(const uint8_t value);
void or(const uint8_t value);
void xor(const uint8_t value);
void cp(const uint8_t value);
void inc(const uint8_t *reg);
void dec(const uint8_t *reg);

// 16-bit arithmetic
void addhl(const uint16_t value);
void addsp(const int8_t value);
void inc16(const uint16_t *reg);
void dec16(const uint16_t *reg);

#endif //ARITHMETIC_H
