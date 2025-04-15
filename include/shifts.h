#ifndef SHIFTS_H
#define SHIFTS_H

#include <stdint.h>

void rlca(void);
void rla(void);
void rrca(void);
void rra(void);
void rlc(uint8_t *reg);
void rl(uint8_t *reg);
void rrc(uint8_t *reg);
void rr(uint8_t *reg);
void sla(uint8_t *reg);
void sra(uint8_t *reg);
void srl(uint8_t *reg);

#endif //SHIFTS_H
