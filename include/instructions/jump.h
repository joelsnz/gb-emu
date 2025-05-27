#ifndef JUMP_H
#define JUMP_H

#include "emulator.h"

void jp(const emu_t *emu);
void jpc(const emu_t *emu);
void jphl(const emu_t *emu);
void jr(const emu_t *emu);
void jrc(const emu_t *emu);

#endif // JUMP_H
