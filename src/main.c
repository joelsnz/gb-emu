#include <arithmetic.h>

#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  cpu_t *cpu = malloc(sizeof(cpu_t));
  init_cpu(cpu);
  cpu->memory[0] = 0x80;
  cpu->memory[1] = 0x00;
  cpu->registers.pc = 0x0;
  cpu->registers.a = 0x03;
  cpu->registers.b = 0x04;

  printf("a: %d\tb: %d\tpc: %d\n", cpu->registers.a, cpu->registers.b, cpu->registers.pc);

  add(cpu);

  printf("a: %d\tb: %d\tpc: %d\n", cpu->registers.a, cpu->registers.b, cpu->registers.pc);

  return 0;
}
