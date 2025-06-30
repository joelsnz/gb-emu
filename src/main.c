#include "ppu.h"

#include <stdlib.h>

int main(int argc, char **argv) {
  if(argc == 2) set_scale(atoi(argv[1]));

  return 0;
}
