#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include "emulator.h"

void swap(emu_t *emu);
void daa(emu_t *emu);
void cpl(emu_t *emu);
void ccf(emu_t *emu);
void scf(emu_t *emu);
void nop(emu_t *emu);
void halt(emu_t *emu); // tbi
void stop(emu_t *emu); // tbi
void di(emu_t *emu);
void ei(emu_t *emu);

#endif //MISCELLANEOUS_H
