#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include <stdint.h>

void swap(uint8_t *reg);
void daa(void);
void cpl(void);
void ccf(void);
void scf(void);
void nop(void);
void halt(void); // tbi
void stop(void); // tbi
void di(void); // tbi
void ei(void); // tbi

#endif //MISCELLANEOUS_H
