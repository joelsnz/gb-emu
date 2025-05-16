#ifndef FLAGS_H
#define FLAGS_H

#define ZERO_FLAG (1 << 7)
#define NEGATIVE_FLAG (1 << 6)
#define HALFCARRY_FLAG (1 << 5)
#define CARRY_FLAG (1 << 4)

#define ISSET_FLAG(cpu, x) (((cpu)->registers.f & (x)) != 0)
#define SET_FLAG(cpu, x) ((cpu)->registers.f |= (x))
#define CLEAR_FLAG(cpu, x) ((cpu)->registers.f &= ~(x))

#endif //FLAGS_H
