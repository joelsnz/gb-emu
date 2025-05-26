#ifndef LOAD_H
#define LOAD_H

#include "emulator.h"

// 8-bit loads
void ld(emu_t *emu);    // r8 <- r8 0x01...
void ldi(emu_t *emu);   // r8 <- imm8 0x00...110
void lda(emu_t *emu);   // a <- r16mem 0x00..1010
void ldfa(emu_t *emu);  // r16mem <- a 0x00..0010
void ldad(emu_t *emu);  // a <- (imm16) 0x11111010
void ldfad(emu_t *emu); // (imm16) <- a 0x11101010
void ldh(emu_t *emu);   // a <- ($ff00 + c) 0x11110010
void ldhf(emu_t *emu);  // ($ff00 + c) <- a 0x11100010
void ldhi(emu_t *emu);  // a <- ($ff00 + imm8) 0x11110000
void ldhfi(emu_t *emu); // ($ff00 + imm8) <- a 0x11100000

// 16-bit loads
void ldi16(emu_t *emu);  // r16 <- imm16 0x00..0001
void ldsp(emu_t *emu);   // (imm16) <- sp 0x00001000
void ldsphl(emu_t *emu); // sp <- hl 0x11111001
void ldhlsp(emu_t *emu); // hl <- sp + imm8 0x11111000
void push(emu_t *emu);
void pop(emu_t *emu);

#endif // LOAD_H
