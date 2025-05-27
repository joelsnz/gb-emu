#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include "emulator.h"

void swap(const emu_t *emu);
void daa(const emu_t *emu);
void cpl(const emu_t *emu);
void ccf(const emu_t *emu);
void scf(const emu_t *emu);
void nop(const emu_t *emu);
void halt(const emu_t *emu); // tbi
void stop(const emu_t *emu); // tbi
void di(const emu_t *emu);
void ei(const emu_t *emu);

#endif //MISCELLANEOUS_H
