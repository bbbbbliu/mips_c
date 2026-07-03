#ifndef RAM_H
#define RAM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct RAM RAM;

/*
** creates instance of ram with
*/
RAM *ram_create(size_t total_size);
uint32_t get_size(RAM *p);
void ram_destroy(RAM *p);

/*
** read byte; returns 8 bit value. Bytes addresses do not have to be aligned
** crashes if address is larger than buffer
*/
uint8_t read_byte(RAM *p, uint32_t address);
/*
** read byte; takes in 8 bit value. Bytes addresses do not have to be aligned
** crashes if address is larger than buffer
*/
void write_byte(RAM *p, uint32_t address, uint8_t volue);

/*
** return half word value (16 bits). Half words address must be half word
* aligned (address mod 2 = 0).
** crashes if address is not half word aligned, or if address is larger than
** buffer
*/
uint16_t read_half(RAM *p, uint32_t address);
/*
** write half word (16 bits). Half words address must be half word aligned
* (address mod 2 = 0).
** crashes if address is not half word aligned, or if address is larger than
** buffer
*/
void write_half(RAM *p, uint32_t address, uint16_t volue);
/*
** returns word (32 bits). Word addresses must be word aligned (address mod 4 =
* 0)
** Crashes if address not word aligned or address is larger than buffer
*/
uint32_t read_word(RAM *p, uint32_t address);
/*
** writes word (32 bits). Word addresses must be word aligned (address mod 4 =
* 0)
** Crashes if address not word aligned or address is larger than buffer
*/
void write_word(RAM *p, uint32_t address, uint32_t volue);

int load_file(RAM *ram, const char *filename, uint32_t load_address);

/**
 * sets all values within ram to zero
 **/
void clear_ram(RAM *p);

/**
 * @brief Prints a formatted hex dump of a section of RAM to stdout.
 *
 * Displays addresses, hex values, and ASCII representations side-by-side
 * (similar to the classic `hexdump -C` command-line utility).
 */
void ram_dump(RAM *ram, uint32_t start_address, size_t length);
#endif // !RAM_H
