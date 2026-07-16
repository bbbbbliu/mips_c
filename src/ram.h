#ifndef RAM_H
#define RAM_H

#include "mips.h"
bool ram_init(System *sys, uint32_t size);

void ram_destroy(System *sys);

#endif // !RAM_H
