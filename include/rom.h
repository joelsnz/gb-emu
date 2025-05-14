#ifndef ROM_H
#define ROM_H

#include "cpu.h"

void boot_sequence(cpu_t *cpu);
int load_rom(cpu_t *cpu, const char *rom_path);

#endif //ROM_H
