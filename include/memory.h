#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

extern uint8_t *memory = malloc(sizeof(uint8_t) * 0xFFFF);

#endif // MEMORY_H
