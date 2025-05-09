#ifndef LOAD_H
#define LOAD_H

#include "cpu.h"

// 8-bit loads
void ld(cpu_t *cpu);    // r8 <- r8 0x01...
void ldi(cpu_t *cpu);   // r8 <- imm8 0x00...110
void lda(cpu_t *cpu);   // a <- r16mem 0x00..1010
void ldfa(cpu_t *cpu);  // r16mem <- a 0x00..0010
void ldad(cpu_t *cpu);  // a <- (imm16) 0x11111010
void ldfad(cpu_t *cpu); // (imm16) <- a 0x11101010
void ldh(cpu_t *cpu);   // a <- ($ff00 + c) 0x11110010
void ldhf(cpu_t *cpu);  // ($ff00 + c) <- a 0x11100010
void ldhi(cpu_t *cpu);  // a <- ($ff00 + imm8) 0x11110000
void ldhfi(cpu_t *cpu); // ($ff00 + imm8) <- a 0x11100000

// 16-bit loads
void ldi16(cpu_t *cpu);  // r16 <- imm16 0x00..0001
void ldsp(cpu_t *cpu);   // (imm16) <- sp 0x00001000
void ldsphl(cpu_t *cpu); // sp <- hl 0x11111001
void ldhlsp(cpu_t *cpu); // hl <- sp + imm8 0x11111000
void push(cpu_t *cpu);
void pop(cpu_t *cpu);

#endif // LOAD_H
