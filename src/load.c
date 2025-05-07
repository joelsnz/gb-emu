#include "load.h"

#include "flags.h"

void ld(cpu_t *cpu) {
  uint8_t *dest = get_middle_r8(cpu);
  uint8_t *source = get_lower_r8(cpu);

  *dest = *source;
}

void ldi(cpu_t *cpu) {
  uint8_t *dest = get_middle_r8(cpu);
  uint8_t imm = get_imm8(cpu);

  *dest = imm;
}

void lda(cpu_t *cpu) {
  uint16_t source = *get_r16mem(cpu);

  cpu->registers.a = cpu->memory[source];
}

void ldfa(cpu_t *cpu) {
  uint8_t dest = *get_r16mem(cpu);

  cpu->memory[dest] = cpu->registers.a;
}

void ldad(cpu_t *cpu) {
  uint16_t addr = get_imm16(cpu);

  cpu->registers.a = cpu->memory[addr];
}

void ldfad(cpu_t *cpu) {
  uint16_t addr = get_imm16(cpu);

  cpu->memory[addr] = cpu->registers.a;
}

void ldh(cpu_t *cpu) {
  uint16_t addr = cpu->registers.c + 0xff00;

  cpu->registers.a = cpu->memory[addr];
}

void ldhf(cpu_t *cpu) {
  uint16_t addr = cpu->registers.c + 0xff00;

  cpu->memory[addr] = cpu->registers.a;
}

void ldhi(cpu_t *cpu) {
  uint8_t imm = get_imm8(cpu);
  uint16_t addr = imm + 0xff00;

  cpu->registers.a = cpu->memory[addr];
}

void ldhfi(cpu_t *cpu) {
  uint8_t imm = get_imm8(cpu);
  uint16_t addr = imm + 0xff00;

  cpu->memory[addr] = cpu->registers.a;
}

void ldi16(cpu_t *cpu) {
  uint16_t *dest = get_r16(cpu);
  uint16_t imm = get_imm16(cpu);

  *dest = imm;
}

void ldsp(cpu_t *cpu) {
  uint16_t addr = get_imm16(cpu);

  cpu->memory[addr] = cpu->registers.sp;
}

void ldsphl(cpu_t *cpu) { cpu->registers.sp = cpu->registers.hl; }

void ldhlsp(cpu_t *cpu) {
  uint8_t imm = get_imm8(cpu);
  uint16_t result = cpu->registers.sp + imm;

  CLEAR_FLAG(cpu, ZERO_FLAG | NEGATIVE_FLAG);

  const uint8_t half_carry =
      (cpu->registers.sp & 0x0F) + (imm & 0x0F) > 0x0F;
  if(half_carry) SET_FLAG(cpu, HALFCARRY_FLAG);
  else CLEAR_FLAG(cpu, HALFCARRY_FLAG);

  if(result > UINT8_MAX) SET_FLAG(cpu, CARRY_FLAG);
  else CLEAR_FLAG(cpu, CARRY_FLAG);

  cpu->registers.hl = result;
}

void push(cpu_t *cpu) {
  uint16_t *sp = &cpu->registers.sp;
  uint16_t *reg = get_r16stk(cpu);

  cpu->memory[--(*sp)] = (*reg >> 8) & 0xFF;
  cpu->memory[--(*sp)] = (*reg) & 0xFF;
}

void pop(cpu_t *cpu) {
  uint16_t *sp = &cpu->registers.sp;
  uint16_t *reg = get_r16stk(cpu);

  *reg = cpu->memory[(*sp)++];
  *reg |= cpu->memory[(*sp)++] << 8;

  if(reg == &cpu->registers.af)
    *reg &= 0xfff0; // f's lsb must be blank
}
