#ifndef SHIFTS_H
#define SHIFTS_H

#include "emulator.h"

void rlca(const emu_t *emu);
void rla(const emu_t *emu);
void rrca(const emu_t *emu);
void rra(const emu_t *emu);
void rlc(const emu_t *emu);
void rl(const emu_t *emu);
void rrc(const emu_t *emu);
void rr(const emu_t *emu);
void sla(const emu_t *emu);
void sra(const emu_t *emu);
void srl(const emu_t *emu);

#endif //SHIFTS_H
