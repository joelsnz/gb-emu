#include "instructions/call.h"

#include "common.h"
#include "cpu.h"
#include "instructions/miscellaneous.h"
#include "mmu.h"

#include <stdint.h>

void call(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;

  const uint16_t ret_addr = cpu->registers.pc + 0x03; // after imm16

  push_to_stack(emu, ret_addr);

  cpu->registers.pc = get_imm16(emu);
}

void callc(const emu_t *emu) {
  const cpu_t *cpu = emu->cpu;
  if(get_cond(cpu)) call(emu);
}

void rst(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;

  const uint16_t ret_addr = cpu->registers.pc;

  push_to_stack(emu, ret_addr);

  cpu->registers.pc = (uint16_t)get_tgt3(cpu) & 0x00FF;
}

void ret(const emu_t *emu) {
  emu->cpu->registers.pc = pop_from_stack(emu);
}

void retc(const emu_t *emu) {
  cpu_t *cpu = emu->cpu;
  if(get_cond(cpu)) ret(emu);
}

void reti(const emu_t *emu) {
  ret(emu);
  ei(emu);
}
