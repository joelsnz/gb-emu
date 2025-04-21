#include "instructions.h"

#include "arithmetic.h"
#include "bit.h"
#include "jump.h"
#include "miscellaneous.h"
#include "shifts.h"

instruction_t base_instr_list[0xFF + 1];
instruction_t prefix_instr_list[0xFF + 1];

void init_arithmetic_list(void) {
  for(int i = 0x80; i <= 0x88; i++) {
    base_instr_list[i].instruction        = add;
    base_instr_list[i + 0x08].instruction = adc;
    base_instr_list[i + 0x10].instruction = sub;
    base_instr_list[i + 0x18].instruction = sbc;
    base_instr_list[i + 0x20].instruction = and_;
    base_instr_list[i + 0x28].instruction = xor_;
    base_instr_list[i + 0x30].instruction = or_;
    base_instr_list[i + 0x38].instruction = cp;
  }
  for(int i = 0x80; i <= 0xbf; i++)
    base_instr_list[i] = (instruction_t){
        .bytes = 1, .cycles = (i & 0x06) == 0x06 ? 2 : 1};

  base_instr_list[0xc6].instruction = add;
  base_instr_list[0xd6].instruction = sub;
  base_instr_list[0xe6].instruction = and_;
  base_instr_list[0xf6].instruction = or_;
  base_instr_list[0xce].instruction = adc;
  base_instr_list[0xde].instruction = sbc;
  base_instr_list[0xee].instruction = xor_;
  base_instr_list[0xfe].instruction = cp;
  for(int i = 0xc6; i <= 0xfe; i += 0x08)
    base_instr_list[i] = (instruction_t){.bytes = 2, .cycles = 2};

  base_instr_list[0xe8] =
      (instruction_t){.instruction = add, .bytes = 2, .cycles = 4};

  for(int i = 0x03; i <= 0x3d; i += 0x08) {
    base_instr_list[i] =
        (instruction_t){.instruction = (i & 0x80) ? dec : inc,
                        .bytes       = 1,
                        .cycles      = 2};
    base_instr_list[i + 1] = (instruction_t){
        .instruction = inc, .bytes = 1, .cycles = i == 0x34 ? 3 : 1};
    base_instr_list[i + 2] = (instruction_t){
        .instruction = dec, .bytes = 1, .cycles = i == 0x34 ? 3 : 1};
  }

  for(int i = 0x09; i <= 0x39; i += 0x10)
    base_instr_list[i] =
        (instruction_t){.instruction = add, .bytes = 1, .cycles = 2};
}

void init_bit_list(void) {
  for(int i = 0x40; i <= 0x7f; i++)
    prefix_instr_list[i] =
        (instruction_t){.instruction = bit,
                        .bytes       = 2,
                        .cycles      = (i & 0x06) == 0x06 ? 3 : 2};
  for(int i = 0x80; i <= 0xbf; i++)
    prefix_instr_list[i] =
        (instruction_t){.instruction = res,
                        .bytes       = 2,
                        .cycles      = (i & 0x06) == 0x06 ? 4 : 2};
  for(int i = 0xc0; i <= 0xff; i++)
    prefix_instr_list[i] =
        (instruction_t){.instruction = set,
                        .bytes       = 2,
                        .cycles      = (i & 0x06) == 0x06 ? 4 : 2};
}

void init_jump_list(cpu_t *cpu) {
  base_instr_list[0xc3] =
      (instruction_t){.instruction = jp, .bytes = 3, .cycles = 4};

  for(int i = 0xc2; i <= 0xda; i += 0x08)
    base_instr_list[i] =
        (instruction_t){.instruction = jpc,
                        .bytes       = 3,
                        .cycles      = get_cond(cpu) ? 4 : 3};

  base_instr_list[0xe9] =
      (instruction_t){.instruction = jphl, .bytes = 1, .cycles = 1};

  base_instr_list[0x18] =
      (instruction_t){.instruction = jr, .bytes = 2, .cycles = 3};

  for(int i = 0x20; i <= 0x38; i += 0x08)
    base_instr_list[i] =
        (instruction_t){.instruction = jrc,
                        .bytes       = 2,
                        .cycles      = get_cond(cpu) ? 3 : 2};
}

void init_misc_list(void) {
  for(int i = 0x30; i <= 0x37; i++) {
    prefix_instr_list[i] = (instruction_t){
        .instruction = swap, .bytes = 2, .cycles = i == 0x36 ? 4 : 2};
  }

  base_instr_list[0x00] =
      (instruction_t){.instruction = nop, .bytes = 1, .cycles = 1};

  base_instr_list[0x10] =
      (instruction_t){.instruction = stop, .bytes = 2, .cycles = 1};

  base_instr_list[0x27] =
      (instruction_t){.instruction = daa, .bytes = 1, .cycles = 1};

  base_instr_list[0x37] =
      (instruction_t){.instruction = scf, .bytes = 1, .cycles = 1};

  base_instr_list[0x2f] =
      (instruction_t){.instruction = cpl, .bytes = 1, .cycles = 1};

  base_instr_list[0x3f] =
      (instruction_t){.instruction = ccf, .bytes = 1, .cycles = 1};

  base_instr_list[0x76] =
      (instruction_t){.instruction = halt, .bytes = 1, .cycles = 1};

  base_instr_list[0xf3] =
      (instruction_t){.instruction = di, .bytes = 1, .cycles = 1};

  base_instr_list[0xfb] =
      (instruction_t){.instruction = ei, .bytes = 1, .cycles = 1};
}

void init_shifts_list(void) {
  base_instr_list[0x07] =
      (instruction_t){.instruction = rlca, .bytes = 1, .cycles = 1};

  base_instr_list[0x17] =
      (instruction_t){.instruction = rla, .bytes = 1, .cycles = 1};

  base_instr_list[0x0f] =
      (instruction_t){.instruction = rrca, .bytes = 1, .cycles = 1};

  base_instr_list[0x1f] =
      (instruction_t){.instruction = rra, .bytes = 1, .cycles = 1};

  for(int i = 0x00; i <= 0x07; i++) {
    base_instr_list[i] =
        (instruction_t){.instruction = rlc,
                        .bytes       = 2,
                        .cycles      = (i & 0x06) == 0x06 ? 4 : 2};
    base_instr_list[i + 0x08] =
        (instruction_t){.instruction = rrc,
                        .bytes       = 2,
                        .cycles      = (i & 0x06) == 0x06 ? 4 : 2};
    base_instr_list[i + 0x10] =
        (instruction_t){.instruction = rl,
                        .bytes       = 2,
                        .cycles      = (i & 0x06) == 0x06 ? 4 : 2};
    base_instr_list[i + 0x18] =
        (instruction_t){.instruction = rr,
                        .bytes       = 2,
                        .cycles      = (i & 0x06) == 0x06 ? 4 : 2};
    base_instr_list[i + 0x20] =
        (instruction_t){.instruction = sla,
                        .bytes       = 2,
                        .cycles      = (i & 0x06) == 0x06 ? 4 : 2};
    base_instr_list[i + 0x28] =
        (instruction_t){.instruction = sra,
                        .bytes       = 2,
                        .cycles      = (i & 0x06) == 0x06 ? 4 : 2};
  }
}

void init_instr_list(cpu_t *cpu) {
  init_arithmetic_list();
  init_bit_list();
  init_jump_list(cpu);
  init_misc_list();
  init_shifts_list();
}
