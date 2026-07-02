#ifndef RAM_H
#define RAM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct RAM RAM;

// ram create and destry functions
RAM *ram_create(size_t total_size);
void ram_destroy(RAM *p);

// write and read word, half words and bytes fcts.
uint32_t read_word(RAM *p, uint32_t address);
void write_word(RAM *p, uint32_t address, uint32_t volue);

uint32_t read_half(RAM *p, uint32_t address);
void write_half(RAM *p, uint32_t address, uint32_t volue);

uint32_t read_byte(RAM *p, uint32_t address);
void write_byte(RAM *p, uint32_t address, uint32_t volue);

int load_file(RAM *ram, const char *filename, uint32_t load_address);

#endif // !RAM_H
