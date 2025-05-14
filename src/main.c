#include "cpu.h"

#include "rom.h"
#include <stdlib.h>

int main(int argc, char **argv) {
  cpu_t *cpu = malloc(sizeof(cpu_t));
  init_cpu(cpu);
  load_rom(cpu, argv[1]);
  boot_sequence(cpu);

  for (int i = 0; i < 8000; i++) cpu_step(cpu);

  return 0;
}
