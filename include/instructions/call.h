#ifndef CALL_H
#define CALL_H

#include "emulator.h"

void call(const emu_t *emu);
void callc(const emu_t *emu);

void rst(const emu_t *emu);

void ret(const emu_t *emu);
void retc(const emu_t *emu);
void reti(const emu_t *emu);

#endif // CALL_H
