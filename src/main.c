#include "cpu.h"
#include "rom.h"
#include "video.h"

#include <stdlib.h>

int main(int argc, char **argv) {
  cpu_t *cpu = malloc(sizeof(cpu_t));
  init_cpu(cpu);
  init_video();
  // load_rom(cpu, rom argv[1]);
  boot_sequence(cpu);

  while(video_step()) {}

  return 0;
}
