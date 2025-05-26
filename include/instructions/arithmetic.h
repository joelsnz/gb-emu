#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "emulator.h"

// 8-bit arithmetic
void add(emu_t *emu);
void adc(emu_t *emu);
void sub(emu_t *emu);
void sbc(emu_t *emu);
void and_(emu_t *emu);
void or_(emu_t *emu);
void xor_(emu_t *emu);
void cp(emu_t *emu);
void inc(emu_t *emu);
void dec(emu_t *emu);

// 16-bit arithmetic
void addhl(emu_t *emu);
void addsp(emu_t *emu);
void inc16(emu_t *emu);
void dec16(emu_t *emu);

#endif //ARITHMETIC_H
