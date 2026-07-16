#include "ram.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*RAM*/
struct RAM {
    uint8_t *buffer;
    size_t size;
};

// ram create and destry functions
/* RAM *ram_create(size_t total_size) { */
/*     RAM *ram = malloc(sizeof(RAM)); */
/*     ram->size = total_size; */
/*     ram->buffer = calloc(total_size, sizeof(uint8_t)); */
/*     return ram; */
/* }; */

bool ram_init(System *sys, uint32_t size) {
    if (sys == NULL || sys->bus == NULL || sys->bus->ram == NULL) {
        return false;
    }
    sys->bus->ram->buffer = calloc(size, 1);
    if (sys->bus->ram->buffer == NULL) {
        sys->bus->ram->size = 0; // consistency on failure
        return false;
    }
    sys->bus->ram->size = size;
    return true;
}

/* uint32_t get_size(RAM *p) { return p->size; } */

void ram_destroy(System *sys) {
    free(sys->bus->ram);
    sys->bus->ram = NULL;
    /* free(ram->buffer); */
    /* ram->buffer = NULL; */
    /* free(ram); */
    /* ram = NULL; */
};

/*
/* ** read byte; returns 8 bit value. Bytes addresses do not have to be aligned
*/
/* ** crashes if address is larger than buffer */
/* *\/ */
/* uint8_t read_byte(const RAM *p, uint32_t address) { return
 * p->buffer[address]; } */
/* /\* */
/* ** read byte; takes in 8 bit value. Bytes addresses do not have to be aligned
 */
/* ** crashes if address is larger than buffer */
/* *\/ */
/* void write_byte(RAM *p, uint32_t address, uint8_t value) { */
/*     p->buffer[address] = value; */
/* } */

/* /\* */
/* ** return half word value (16 bits). Half words address must be half word */
/* * aligned (address mod 2 = 0). */
/* ** crashes if address is not half word aligned, or if address is larger than
 */
/* ** buffer */
/* *\/ */
/* uint16_t read_half(const RAM *p, uint32_t address) { */
/*     return ((uint16_t)p->buffer[address + 1] << 8) | */
/*            (uint16_t)p->buffer[address]; */
/* } */
/* /\* */
/* ** write half word (16 bits). Half words address must be half word aligned */
/* * (address mod 2 = 0). */
/* ** crashes if address is not half word aligned, or if address is larger than
 */
/* ** buffer */
/* *\/ */
/* void write_half(RAM *p, uint32_t address, uint16_t value) { */
/*     // assert(address < p->size - 1); */
/*     // assert(0 == (address & 1)); */
/*     p->buffer[address] = value; */
/*     p->buffer[address + 1] = value >> 8; */
/* } */
/* /\* */
/* ** returns word (32 bits). Word addresses must be word aligned (address mod 4
 * = */
/* * 0) */
/* ** Crashes if address not word aligned or address is larger than buffer */
/* *\/ */
/* uint32_t read_word(const RAM *p, uint32_t address) { */
/*     // assert(address < p->size - 3); */
/*     // assert(0 == (address & 3)); */
/*     return ((uint32_t)p->buffer[address]) | */
/*            ((uint32_t)p->buffer[address + 1] << 8) | */
/*            ((uint32_t)p->buffer[address + 2] << 16) | */
/*            ((uint32_t)p->buffer[address + 3] << 24); */
/* } */
/* /\* */
/* ** writes word (32 bits). Word addresses must be word aligned (address mod 4
 * = */
/* * 0) */
/* ** Crashes if address not word aligned or address is larger than buffer */
/* *\/ */
/* void write_word(RAM *p, uint32_t address, uint32_t value) { */
/*     // assert(address < p->size - 3); */
/*     // assert(0 == (address & 3)); */
/*     p->buffer[address] = value; */
/*     p->buffer[address + 1] = value >> 8; */
/*     p->buffer[address + 2] = value >> 16; */
/*     p->buffer[address + 3] = value >> 24; */
/* } */
/* int load_file(RAM *ram, const char *filename, uint32_t load_address) { */
/*     if (load_address >= ram->size) { */
/*         return -1; // invalid start address */
/*     } */
/*     FILE *file = fopen(filename, "rb"); */
/*     if (file == NULL) { */
/*         return -2; // file couldn't be opened (DNE or improper permissions)
 */
/*     } */
/*     fseek(file, 0, SEEK_END); */
/*     long file_size = ftell(file); */
/*     fseek(file, 0, SEEK_SET); */

/*     if (file_size < 0) { */
/*         fclose(file); */
/*         return -3; // File system error reading file size */
/*     } */
/*     if (load_address + (size_t)file_size > ram->size) { */
/*         fclose(file); */
/*         return -4; // file is too large to fit into ram */
/*     } */
/*     size_t bytes_read = */
/*         fread(&ram->buffer[load_address], 1, (size_t)file_size, file); */
/*     fclose(file); */
/*     if (bytes_read != (size_t)file_size) { */
/*         return -5; // Read error occured */
/*     } */

/*     return 0; // success */
/* } */

/* /\** */
/*  * sets all values within ram to zero */
/*  **\/ */
/* void clear_ram(RAM *p) { memset(p->buffer, 0, p->size); } */

/* /\** */
/*  * @brief Prints a formatted hex dump of a section of RAM to stdout. */
/*  * */
/*  * Displays addresses, hex values, and ASCII representations side-by-side */
/*  * (similar to the classic `hexdump -C` command-line utility). */
/*  *\/ */
/* // In ram.h */
/* void ram_dump(FILE *stream, RAM *ram, uint32_t start_address, size_t length)
 * { */
/*     if (ram == NULL || stream == NULL) { */
/*         return; */
/*     } */

/*     // Guard against overflowing the virtual RAM buffer */
/*     if (start_address >= ram->size) { */
/*         fprintf(stream, */
/*                 "RAM Dump Error: Start address 0x%08X is out of bounds.\n",
 */
/*                 start_address); */
/*         return; */
/*     } */

/*     // Clamp the length if it would spill past the end of RAM */
/*     if (start_address + length > ram->size) { */
/*         length = ram->size - start_address; */
/*     } */

/*     fprintf(stream, "--- RAM DUMP (Start: 0x%08X, Length: %zu bytes) ---\n",
 */
/*             start_address, length); */

/*     // Print out memory in neat blocks of 16 bytes per line */
/*     for (size_t i = 0; i < length; i += 16) { */
/*         uint32_t current_addr = start_address + (uint32_t)i; */

/*         // 1. Print the memory address header (e.g., 00001000:) */
/*         fprintf(stream, "0x%08X: ", current_addr); */

/*         // 2. Print 16 bytes in Hexadecimal format */
/*         for (size_t j = 0; j < 16; j++) { */
/*             if (i + j < length) { */
/*                 fprintf(stream, "%02X ", ram->buffer[current_addr + j]); */
/*             } else { */
/*                 fprintf(stream, "   "); // Padding spaces if we run out of
 * data */
/*                                         // on the last line */
/*             } */
/*         } */

/*         fprintf(stream, " | "); */

/*         // 3. Print the same 16 bytes as ASCII characters (helps spot strings
 * in */
/*         // memory) */
/*         for (size_t j = 0; j < 16; j++) { */
/*             if (i + j < length) { */
/*                 uint8_t byte = ram->buffer[current_addr + j]; */
/*                 // isprint checks if the character can be typed/seen
 * (letters, */
/*                 // numbers, space) */
/*                 fprintf(stream, "%c", isprint(byte) ? byte : '.'); */
/*             } */
/*         } */

/*         fprintf(stream, "\n"); */
/*     } */
/*     fprintf(stream, */
/*             "---------------------------------------------------------\n");
 */
}
