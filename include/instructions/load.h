#ifndef LOAD_H
#define LOAD_H

#include "emulator.h"

// 8-bit loads
void ld(const emu_t *emu);    // r8 <- r8 0x01...
void ldi(const emu_t *emu);   // r8 <- imm8 0x00...110
void lda(const emu_t *emu);   // a <- r16mem 0x00..1010
void ldfa(const emu_t *emu);  // r16mem <- a 0x00..0010
void ldad(const emu_t *emu);  // a <- (imm16) 0x11111010
void ldfad(const emu_t *emu); // (imm16) <- a 0x11101010
void ldh(const emu_t *emu);   // a <- ($ff00 + c) 0x11110010
void ldhf(const emu_t *emu);  // ($ff00 + c) <- a 0x11100010
void ldhi(const emu_t *emu);  // a <- ($ff00 + imm8) 0x11110000
void ldhfi(const emu_t *emu); // ($ff00 + imm8) <- a 0x11100000

// 16-bit loads
void ldi16(const emu_t *emu);  // r16 <- imm16 0x00..0001
void ldsp(const emu_t *emu);   // (imm16) <- sp 0x00001000
void ldsphl(const emu_t *emu); // sp <- hl 0x11111001
void ldhlsp(const emu_t *emu); // hl <- sp + imm8 0x11111000
void push(const emu_t *emu);
void pop(const emu_t *emu);

#endif // LOAD_H
