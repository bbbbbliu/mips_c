#ifndef MIPS_H
#define MIPS_H

#include <cstddef>
#include <stdint.h>
typedef struct {
    uint32_t gpr[32]; // general purpose registers
    uint32_t pc;      // program counter
    uint32_t hi, lo;  //
} CPU;

typedef struct {
    uint8_t *ram;
    size_t size;
} BUS;

typedef struct {
    CPU cpu;
    BUS bus;

} System;

#endif // MIPS_H_
