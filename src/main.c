#include "cpu.h"

#include <instructions/arithmetic.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  cpu_t *cpu = malloc(sizeof(cpu_t));
  init_cpu(cpu);
  cpu->memory.raw[0] = 0xc3;
  cpu->memory.raw[1] = 0x20;
  cpu->memory.raw[2] = 0x00;
  cpu->registers.pc = 0x0;
  cpu->registers.a = 0x0;

  printf("a: %d\tb: %d\tpc: %d\n", cpu->registers.a, cpu->registers.b,
         cpu->registers.pc);

  cpu_step(cpu);

  printf("a: %d\tb: %d\tpc: %d\n", cpu->registers.a, cpu->registers.b,
         cpu->registers.pc);

  return 0;
}
