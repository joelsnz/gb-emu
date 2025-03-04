#include "registers.h"

#include "cpu.h"

void add(op) {
  uint8_t result = registers.a + op;
}
