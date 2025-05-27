#ifndef EMULATOR_H
#define EMULATOR_H

// forward declarations
typedef struct cpu_t cpu_t;
typedef union mmu_t mmu_t;
typedef struct lcd_t lcd_t;

typedef struct emulator {
  cpu_t *cpu;
  mmu_t *mmu;
  lcd_t *lcd;
} emu_t;

#endif //EMULATOR_H
