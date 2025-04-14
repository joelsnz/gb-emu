#ifndef CPU_H
#define CPU_H

#include <stdint.h>

int prefix_execute(const uint8_t opcode);
int execute(const uint8_t opcode);
void step();

#endif //CPU_H