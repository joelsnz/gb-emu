#include <cpu.h>
#include <memory.h>
#include <registers.h>
#include <stdio.h>

int main(void) {
  memory[0] = 0xCB;
  memory[1] = 0x00;
  registers.pc = 0x0;
  registers.a = 0x03;
  registers.b = 0x04;

  printf("a: %d\tb: %d\tpc: %d\n", registers.a, registers.b, registers.pc);

  step();

  printf("a: %d\tb: %d\tpc: %d\n", registers.a, registers.b, registers.pc);

  return 0;
}
