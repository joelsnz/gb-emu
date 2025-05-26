#ifndef CALL_H
#define CALL_H

#include "emulator.h"

void call(emu_t *emu);
void callc(emu_t *emu);

void rst(emu_t *emu);

void ret(emu_t *emu);
void retc(emu_t *emu);
void reti(emu_t *emu);

#endif // CALL_H
