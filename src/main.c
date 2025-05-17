#include "cpu.h"

#include "rom.h"
#include <stdlib.h>

int main(int argc, char **argv) {
  cpu_t *cpu = malloc(sizeof(cpu_t));
  init_cpu(cpu);
  const char rom[] = "../../../Documents/01-special.gb";
  load_rom(cpu, rom /*argv[1]*/);
  boot_sequence(cpu);

  while (1) cpu_step(cpu);

  return 0;
}
