#ifndef MIPS_H
#define MIPS_H
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint32_t gpr[32]; // general purpose registers
    uint32_t pc;      // program counter
    uint32_t hi, lo;  //
} CPUstate;

typedef struct {
    uint8_t *ram;
    size_t size;
} BUSstate;

typedef struct {
    CPUstate cpu;
    BUSstate bus;
} Computer;

#endif // MIPS_H_
