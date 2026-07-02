#include "ram.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/*RAM*/
struct RAM {
  uint8_t *buffer;
  size_t size;
};

// ram create and destry functions
RAM *ram_create(size_t total_size) {
  RAM *ram = malloc(sizeof(RAM));
  assert(ram != NULL);
  ram->size = total_size;
  ram->buffer = calloc(total_size, sizeof(uint8_t));
  assert(ram->buffer != NULL);
  return ram;
};
void ram_destroy(RAM *ram) {
  free(ram->buffer);
  ram->buffer = NULL;
  free(ram);
  ram = NULL;
};
// write and read word, half words and bytes fcts.
uint32_t read_word(RAM *ram, uint32_t address) {
  assert(address % 4 == 0 && "Unaligned word read!");
  assert(address + 3 < ram->size);
  return (ram->buffer[address] << 0x18) | (ram->buffer[address + 1] << 0x10) |
         (ram->buffer[address + 2] << 0x08) |
         (ram->buffer[address + 3] << 0x00);
};
void write_word(RAM *ram, uint32_t address, uint32_t value) {
  assert(address % 4 == 0 && "Unaligned word read!");
  assert(address + 3 < ram->size);
};

uint32_t read_half(RAM *ram, uint32_t address);
void write_half(RAM *ram, uint32_t address, uint32_t value);

uint32_t read_byte(RAM *ram, uint32_t address);
void write_byte(RAM *ram, uint32_t address, uint32_t value);
