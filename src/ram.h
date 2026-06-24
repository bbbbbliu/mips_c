#ifndef RAM_H
#define RAM_H

#include <stdbool.h>
#include <stdint.h>

typedef struct RAM RAM;

RAM *ram_create(void);
void ram_destroy(RAM *p);

void write_ram(RAM *p, uint32_t address);
uint32_t read_ram(RAM *p, uint32_t address, uint32_t volue);

#endif // !RAM_H
