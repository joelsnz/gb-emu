#include "instructions/instructions.h"

#include "instructions/arithmetic.h"
#include "instructions/bit.h"
#include "instructions/call.h"
#include "instructions/jump.h"
#include "instructions/load.h"
#include "instructions/miscellaneous.h"
#include "instructions/shifts.h"

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
                        .bytes = 1,
                        .cycles = 2};
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
                        .bytes = 2,
                        .cycles = (i & 0x06) == 0x06 ? 3 : 2};
  for(int i = 0x80; i <= 0xbf; i++)
    prefix_instr_list[i] =
        (instruction_t){.instruction = res,
                        .bytes = 2,
                        .cycles = (i & 0x06) == 0x06 ? 4 : 2};
  for(int i = 0xc0; i <= 0xff; i++)
    prefix_instr_list[i] =
        (instruction_t){.instruction = set,
                        .bytes = 2,
                        .cycles = (i & 0x06) == 0x06 ? 4 : 2};
}

void init_call_list(cpu_t *cpu) {
  base_instr_list[0xcd] =
      (instruction_t){.instruction = call, .bytes = 3, .cycles = 6};

  for(int i = 0xc4; i <= 0xdc; i += 0x08)
    base_instr_list[i] =
        (instruction_t){.instruction = callc,
                        .bytes = 3,
                        .cycles = get_cond(cpu) ? 6 : 3};

  for(int i = 0xc7; i <= 0xff; i += 0x08)
    base_instr_list[i] =
        (instruction_t){.instruction = rst, .bytes = 1, .cycles = 4};

  base_instr_list[0xc9] =
      (instruction_t){.instruction = ret, .bytes = 1, .cycles = 4};

  for(int i = 0xc0; i <= 0xd8; i += 0x08)
    base_instr_list[i] =
        (instruction_t){.instruction = rst,
                        .bytes = 1,
                        .cycles = get_cond(cpu) ? 5 : 2};

  base_instr_list[0xd9] =
      (instruction_t){.instruction = reti, .bytes = 1, .cycles = 4};
}

void init_jump_list(cpu_t *cpu) {
  base_instr_list[0xc3] =
      (instruction_t){.instruction = jp, .bytes = 3, .cycles = 4};

  for(int i = 0xc2; i <= 0xda; i += 0x08)
    base_instr_list[i] =
        (instruction_t){.instruction = jpc,
                        .bytes = 3,
                        .cycles = get_cond(cpu) ? 4 : 3};

  base_instr_list[0xe9] =
      (instruction_t){.instruction = jphl, .bytes = 1, .cycles = 1};

  base_instr_list[0x18] =
      (instruction_t){.instruction = jr, .bytes = 2, .cycles = 3};

  for(int i = 0x20; i <= 0x38; i += 0x08)
    base_instr_list[i] =
        (instruction_t){.instruction = jrc,
                        .bytes = 2,
                        .cycles = get_cond(cpu) ? 3 : 2};
}

void init_load_list(void) {
  for(int i = 0x01; i <= 0x31; i += 0x10) {
    base_instr_list[i] = (instruction_t){
        .instruction = ldi16, .bytes = 3, .cycles = 3};
    base_instr_list[i + 0x01] =
        (instruction_t){.instruction = ldfa, .bytes = 1, .cycles = 2};
    base_instr_list[i + 0x05] = (instruction_t){
        .instruction = ldi, .bytes = 2, .cycles = i == 0x31 ? 3 : 2};
    base_instr_list[i + 0x09] =
        (instruction_t){.instruction = lda, .bytes = 1, .cycles = 2};
    base_instr_list[i + 0x0d] =
        (instruction_t){.instruction = ldi, .bytes = 2, .cycles = 2};
  }

  base_instr_list[0x08] =
      (instruction_t){.instruction = ldsp, .bytes = 3, .cycles = 5};

  for(int i = 0x04; i <= 0x7f; i++) {
    if(i == 0x76) continue;  // halt
    uint8_t is_indirect = 0; // hl register is involved
    if((i & 0x06) == 0x06 || (i & 0xf8) == 0x70) is_indirect = 1;
    base_instr_list[i] = (instruction_t){
        .instruction = ld, .bytes = 1, .cycles = is_indirect ? 2 : 1};
  }

  base_instr_list[0xe0] =
      (instruction_t){.instruction = ldhfi, .bytes = 2, .cycles = 3};
  base_instr_list[0xf0] =
      (instruction_t){.instruction = ldhi, .bytes = 2, .cycles = 3};

  base_instr_list[0xe2] =
      (instruction_t){.instruction = ldhf, .bytes = 1, .cycles = 2};
  base_instr_list[0xf2] =
      (instruction_t){.instruction = ldh, .bytes = 1, .cycles = 2};

  base_instr_list[0xea] =
      (instruction_t){.instruction = ldfad, .bytes = 3, .cycles = 4};
  base_instr_list[0xfa] =
      (instruction_t){.instruction = ldad, .bytes = 3, .cycles = 4};

  for(int i = 0xc1; i <= 0xf1; i += 0x10) {
    base_instr_list[i] =
        (instruction_t){.instruction = pop, .bytes = 1, .cycles = 3};
    base_instr_list[i + 0x04] =
        (instruction_t){.instruction = push, .bytes = 1, .cycles = 4};
  }
  base_instr_list[0xf8] =
      (instruction_t){.instruction = ldhlsp, .bytes = 2, .cycles = 3};

  base_instr_list[0xf9] =
      (instruction_t){.instruction = ldsphl, .bytes = 1, .cycles = 2};
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
    prefix_instr_list[i] =
        (instruction_t){.instruction = rlc,
                        .bytes = 2,
                        .cycles = (i & 0x06) == 0x06 ? 4 : 2};
    prefix_instr_list[i + 0x08] =
        (instruction_t){.instruction = rrc,
                        .bytes = 2,
                        .cycles = (i & 0x06) == 0x06 ? 4 : 2};
    prefix_instr_list[i + 0x10] =
        (instruction_t){.instruction = rl,
                        .bytes = 2,
                        .cycles = (i & 0x06) == 0x06 ? 4 : 2};
    prefix_instr_list[i + 0x18] =
        (instruction_t){.instruction = rr,
                        .bytes = 2,
                        .cycles = (i & 0x06) == 0x06 ? 4 : 2};
    prefix_instr_list[i + 0x20] =
        (instruction_t){.instruction = sla,
                        .bytes = 2,
                        .cycles = (i & 0x06) == 0x06 ? 4 : 2};
    prefix_instr_list[i + 0x28] =
        (instruction_t){.instruction = sra,
                        .bytes = 2,
                        .cycles = (i & 0x06) == 0x06 ? 4 : 2};
  }
}

void init_instr_list(cpu_t *cpu) {
  init_arithmetic_list();
  init_bit_list();
  init_call_list(cpu);
  init_jump_list(cpu);
  init_load_list();
  init_misc_list();
  init_shifts_list();
}
