#include "rom.h"
#include "memory.h"

#include <stdio.h>

void boot_sequence(cpu_t *cpu) {
	cpu->registers.af = 0x01B0;
	cpu->registers.bc = 0x0013;
	cpu->registers.de = 0x00D8;
	cpu->registers.hl = 0x014D;
	cpu->registers.sp = 0xFFFE;
	cpu->registers.pc = 0x0;

	cpu->memory.raw[0xFF50] = 0;
}

int load_rom(cpu_t *cpu, const char *rom_path) {
	FILE *rom = fopen(rom_path, "rb");

	if(!rom) {
		printf("Can't open rom");
		return 0;
	}

	fseek(rom, 0, SEEK_END);
	size_t size = ftell(rom);
	rewind(rom);

	fread(cpu->memory.rom, 1, size, rom);

	fclose(rom);

	return 1;
}