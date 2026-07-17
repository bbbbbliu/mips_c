#ifndef BUS_H
#define BUS_H

#include "mips.h"

int bus_init(Computer *sys, uint32_t size);

int bus_destroy(Computer *sys);

int read_byte(const Computer *sys, uint32_t address, uint8_t *output);
int write_byte(Computer *sys, uint32_t address, uint8_t value);

int read_half_word(const Computer *sys, uint32_t address, uint16_t *output);
int write_half_word(Computer *sys, uint32_t address, uint16_t value);

int read_word(const Computer *sys, uint32_t address, uint32_t *output);
int write_word(Computer *sys, uint32_t address, uint32_t value);
#endif /* BUS_H */
