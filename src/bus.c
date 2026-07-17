#include "bus.h"
#include "common.h"
#include <stdint.h>
#include <stdlib.h>
/*RAM*/
struct RAM {
    uint8_t *bus.ram;
    size_t size;
};

// ram create and destry functions
/* RAM *ram_create(size_t total_size) { */
/*     RAM *ram = malloc(sizeof(RAM)); */
/*     ram->size = total_size; */
/*     ram->bus.ram = calloc(total_size, sizeof(uint8_t)); */
/*     return ram; */
/* }; */
int bus_init(Computer *sys, uint32_t size) {
    VALIDATE_PTR(sys);
    sys->bus.ram = calloc(size, 1);
    if (sys->bus.ram == NULL) {
        sys->bus.size = 0; // consistency on failure
        return -2;         // calloc failed
    }
    sys->bus.size = size;
    return ERR_SUCCESS;
}

/* uint32_t get_size(RAM *p) { return p->size; } */

int bus_destroy(Computer *sys) {
    VALIDATE_PTR(sys);
    free(sys->bus.ram);
    sys->bus.ram = NULL;
    sys->bus.size = 0;
    return ERR_SUCCESS;
}

/* ** read byte; returns 8 bit value. Bytes addresses do not have to be aligned
** crashes if address is larger than bus.ram
*/
int read_byte(const Computer *p, uint32_t address, uint8_t *return_value) {
    VALIDATE_PTR(p);
    VALIDATE_PTR(return_value);
    *return_value = p->bus.ram[address];

    return ERR_SUCCESS;
}
/*
** read byte; takes in 8 bit value. Bytes addresses do not have to be aligned
** crashes if address is larger than bus.ram
*/
int write_byte(Computer *p, uint32_t address, uint8_t value) {
    VALIDATE_PTR(p);
    p->bus.ram[address] = value;
    return ERR_SUCCESS;
}

/*
** return half word value (16 bits). Half words address must be half word
* aligned (address mod 2 = 0).
** crashes if address is not half word aligned, or if address is larger than
** bus.ram
*/
int read_half(const Computer *p, uint32_t address, uint16_t *return_value) {
    VALIDATE_PTR(p);
    VALIDATE_PTR(return_value);
    if ((address & 0x01) != 0) {
        return ERR_ALIGNMENT;
    }
    *return_value = ((uint16_t)p->bus.ram[address + 1] << 8) |
                    ((uint16_t)p->bus.ram[address]);
    return ERR_SUCCESS;
}
/*
** write half word (16 bits). Half words address must be half word aligned
* (address mod 2 = 0).
** crashes if address is not half word aligned, or if address is larger than
** bus.ram
*/
int write_half(Computer *p, uint32_t address, uint16_t value) {
    VALIDATE_PTR(p);
    // assert(address < p->size - 1);
    // assert(0 == (address & 1));
    p->bus.ram[address] = value;
    p->bus.ram[address + 1] = value >> 8;
}
/*
** returns word (32 bits). Word addresses must be word aligned (address mod 4
=
* 0)
** Crashes if address not word aligned or address is larger than bus.ram
*/
/* uint32_t read_word(const RAM *p, uint32_t address) { */
/*     // assert(address < p->size - 3); */
/*     // assert(0 == (address & 3)); */
/*     return ((uint32_t)p->bus.ram[address]) | */
/*            ((uint32_t)p->bus.ram[address + 1] << 8) | */
/*            ((uint32_t)p->bus.ram[address + 2] << 16) | */
/*            ((uint32_t)p->bus.ram[address + 3] << 24); */
/* } */
/* /\* */
/* ** writes word (32 bits). Word addresses must be word aligned (address mod 4
 * = */
/* * 0) */
/* ** Crashes if address not word aligned or address is larger than bus.ram */
/* *\/ */
/* void write_word(RAM *p, uint32_t address, uint32_t value) { */
/*     // assert(address < p->size - 3); */
/*     // assert(0 == (address & 3)); */
/*     p->bus.ram[address] = value; */
/*     p->bus.ram[address + 1] = value >> 8; */
/*     p->bus.ram[address + 2] = value >> 16; */
/*     p->bus.ram[address + 3] = value >> 24; */
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
/*         fread(&ram->bus.ram[load_address], 1, (size_t)file_size, file); */
/*     fclose(file); */
/*     if (bytes_read != (size_t)file_size) { */
/*         return -5; // Read error occured */
/*     } */

/*      return ERR_SUCCESS; // success */
/* } */

/* /\** */
/*  * sets all values within ram to zero */
/*  **\/ */
/* void clear_ram(RAM *p) { memset(p->bus.ram, 0, p->size); } */

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

/*     // Guard against overflowing the virtual RAM bus.ram */
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
/*                 fprintf(stream, "%02X ", ram->bus.ram[current_addr + j]); */
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
/*                 uint8_t byte = ram->bus.ram[current_addr + j]; */
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
