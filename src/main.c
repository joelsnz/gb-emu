#include "cpu.h"

#include <arithmetic.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  cpu_t *cpu = malloc(sizeof(cpu_t));
  init_cpu(cpu);
  cpu->memory[0] = 0xc6;
  cpu->memory[1] = 0x05;
  cpu->registers.pc = 0x0;
  cpu->registers.a = 0x03;

  printf("a: %d\tb: %d\tpc: %d\n", cpu->registers.a, cpu->registers.b,
         cpu->registers.pc);

  step(cpu);

  printf("a: %d\tb: %d\tpc: %d\n", cpu->registers.a, cpu->registers.b,
         cpu->registers.pc);

  return 0;
}
