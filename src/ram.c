#include "ram.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*RAM*/
struct RAM {
  uint8_t *buffer;
  size_t size;
};

// ram create and destry functions
RAM ram_create(size_t total_size) {

};
void ram_destroy(RAM *p);
