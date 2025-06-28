#include "cpu.h"
#include "lcd.h"
#include "rom.h"

#include <stdlib.h>

int main(int argc, char **argv) {
  if(argc == 2) lcd_set_scale(atoi(argv[1]));

  return 0;
}
