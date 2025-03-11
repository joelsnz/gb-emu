#ifndef CPU_H
#define CPU_H

#include <stdint.h>

// 8-bit ALU
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

// miscellaneous
void swap(const uint8_t *reg);
void daa(void);
void cpl(void);
void ccf(void);
void scf(void);
void nop(void);
void halt(void); // tbi
void stop(void); // tbi
void di(void); // tbi
void ei(void); // tbi

// rotates & shifts
void rlca(void);
void rla(void);
void rrca(void);
void rra(void);
void rlc(const uint8_t *reg);
void rl(const uint8_t *reg);
void rrc(const uint8_t *reg);
void rr(const uint8_t *reg);
void sla(const uint8_t *reg);
void sra(const uint8_t *reg);
void srl(const uint8_t *reg);

// bit opcodes
void bit(uint8_t index, uint8_t *reg);
void set(uint8_t index, uint8_t *reg);
void res(uint8_t index, uint8_t *reg);

#endif // CPU_H
