#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "emulator.h"

// 8-bit arithmetic
void add(const emu_t *emu);
void adc(const emu_t *emu);
void sub(const emu_t *emu);
void sbc(const emu_t *emu);
void and_(const emu_t *emu);
void or_(const emu_t *emu);
void xor_(const emu_t *emu);
void cp(const emu_t *emu);
void inc(const emu_t *emu);
void dec(const emu_t *emu);

// 16-bit arithmetic
void addhl(const emu_t *emu);
void addsp(const emu_t *emu);
void inc16(const emu_t *emu);
void dec16(const emu_t *emu);

#endif //ARITHMETIC_H
