#ifndef REGISTERS
#define REGISTERS

#define ZERO_FLAG (1 << 7)
#define NEGATIVE_FLAG (1 << 6)
#define HALFCARRY_FLAG (2 << 5)
#define CARRY_FLAG (1 << 4)

#define ISSET_FLAG(x) (registers.f & (x))
#define SET_FLAG(x) (registers.f |= (x))
#define CLEAR_FLAG(x) (registers.f &= ~(x))

#include <stdint.h>

struct registers {
  union {
    struct {
      uint8_t a;
      uint8_t f;
    };
    uint16_t af;  
  };
  union {
    struct {
      uint8_t b;
      uint8_t c;
    };
    uint16_t bc;  
  };
  union {
    struct {
      uint8_t d;
      uint8_t e;
    };
    uint16_t de;  
  };
  union {
    struct {
      uint8_t h;
      uint8_t l;
    };
    uint16_t hl;  
  };
  uint16_t sp;
  uint16_t pc;
} extern registers;

#endif // REGISTERS
