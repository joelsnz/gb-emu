#include <stdio.h>

#include "registers.h"

void init_r8(registers_t *r, uint8_t **table) {
	table[0] = &r->b;
	table[1] = &r->c;
	table[2] = &r->d;
	table[3] = &r->e;
	table[4] = &r->h;
	table[5] = &r->l;
	table[6]= NULL;
	table[7] = &r->a;
}