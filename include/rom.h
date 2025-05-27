#ifndef ROM_H
#define ROM_H

#include "emulator.h"

void boot_sequence(const emu_t *emu);
int load_rom(const emu_t *emu, const char *rom_path);

#endif //ROM_H
