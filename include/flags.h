#ifndef FLAGS_H
#define FLAGS_H

#define ZERO_FLAG (1 << 7)
#define NEGATIVE_FLAG (1 << 6)
#define HALFCARRY_FLAG (2 << 5)
#define CARRY_FLAG (1 << 4)

#define ISSET_FLAG(x) ((registers.f & (x)) ? 1 : 0)
#define SET_FLAG(x) (registers.f |= (x))
#define CLEAR_FLAG(x) (registers.f &= ~(x))

#endif //FLAGS_H
