#include "instructions.h"

#include "arithmetic.h"
#include "bit.h"
#include "miscellaneous.h"
#include "shifts.h"

instruction_t base_instr_list[0xFF + 1];
instruction_t prefix_instr_list[0xFF + 1];

void init_arithmetic_list(void) {
  for(int i = 0x80; i <= 0x88; i++) {
    base_instr_list[i].instruction = add;
    base_instr_list[i + 0x08].instruction = adc;
    base_instr_list[i + 0x10].instruction = sub;
    base_instr_list[i + 0x18].instruction = sbc;
    base_instr_list[i + 0x20].instruction = and_;
    base_instr_list[i + 0x28].instruction = xor_;
    base_instr_list[i + 0x30].instruction = or_;
    base_instr_list[i + 0x38].instruction = cp;
  }
  for(int i = 0x80; i <= 0xbf; i++) {
    base_instr_list[i].bytes = 1;
    base_instr_list[i].cycles = (i & 0x06) ? 2 : 1;
  }

  base_instr_list[0xc6].instruction = add;
  base_instr_list[0xd6].instruction = sub;
  base_instr_list[0xe6].instruction = and_;
  base_instr_list[0xf6].instruction = or_;
  base_instr_list[0xce].instruction = adc;
  base_instr_list[0xde].instruction = sbc;
  base_instr_list[0xee].instruction = xor_;
  base_instr_list[0xfe].instruction = cp;
  for(int i = 0xc6; i <= 0xfe; i += 0x08) {
    base_instr_list[i].bytes = 2;
    base_instr_list[i].cycles = 2;
  }

  base_instr_list[0xe8].instruction = add;
  base_instr_list[0xe8].bytes = 2;
  base_instr_list[0xe8].cycles = 4;

  for(int i = 0x03; i <= 0x3d; i += 0x08) {
    base_instr_list[i].instruction = (i & 0x80) ? dec : inc;
    base_instr_list[i].bytes = 1;
    base_instr_list[i].cycles = 2;
    base_instr_list[i + 1].instruction = inc;
    base_instr_list[i + 1].bytes = 1;
    base_instr_list[i + 1].cycles = i == 0x34 ? 3 : 1;
    base_instr_list[i + 2].instruction = dec;
    base_instr_list[i + 2].bytes = 1;
    base_instr_list[i + 2].cycles = i == 0x34 ? 3 : 1;
  }

  for(int i = 0x09; i <= 0x39; i += 0x10) {
    base_instr_list[i].instruction = add;
    base_instr_list[i].bytes = 1;
    base_instr_list[i].cycles = 2;
  }
}

void init_instr_list(void) { init_arithmetic_list(); }
