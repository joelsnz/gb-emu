#include "load.h"

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
  uint8_t *reg = get_r16mem(cpu);

  cpu->registers.a = *reg;
}

void ldfa(cpu_t *cpu) {}

void ldad(cpu_t *cpu) {}

void ldfad(cpu_t *cpu) {}

void ldh(cpu_t *cpu) {}

void ldhf(cpu_t *cpu) {}

void ldhi(cpu_t *cpu) {}

void ldhfi(cpu_t *cpu) {}

void ld16(cpu_t *cpu) {}

void ldi16(cpu_t *cpu) {}

void ldsp(cpu_t *cpu) {}

void ldsphl(cpu_t *cpu) {}

void ldhlsp(cpu_t *cpu) {}

void push(cpu_t *cpu) {}

void pop(cpu_t *cpu) {}
