#include "rom.h"
#include "mmu.h"
#include "cpu.h"

#include <stdio.h>

void boot_sequence(const emu_t *emu) {
  registers_t *reg = &emu->cpu->registers;
  mmu_t *mmu = emu->mmu;
	reg->af = 0x01B0;
	reg->bc = 0x0013;
	reg->de = 0x00D8;
	reg->hl = 0x014D;
	reg->sp = 0xFFFE;
	reg->pc = 0x0;

	mmu->raw[0xFF50] = 0;
}

int load_rom(const emu_t *emu, const char *rom_path) {
  mmu_t *mmu = emu->mmu;
	FILE *rom = fopen(rom_path, "rb");

	if(!rom) {
		printf("Can't open rom");
		return 0;
	}

	fseek(rom, 0, SEEK_END);
	const size_t size = ftell(rom);
	rewind(rom);

	fread(mmu->rom, 1, size, rom);

	fclose(rom);

	return 1;
}