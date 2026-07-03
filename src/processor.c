#include "processor.h"
#include <stdbool.h>
#include <stdint.h>
// #include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct CPU {
    /* General Purpose Registers
     * Не забудь:
     * $0 всегда возвращает 0!
     * $31 (називается $ra, return address) есть обратный адрес
     * */
    uint32_t gpr[31];

    /* Multiply/Divide */
    uint32_t hi;
    uint32_t lo;

    /* Program Counters*/
    uint32_t pc;
    // uint32_t pc_next; /* необязательный для branch-delay */
};
// methods for creating mips instance
CPU *cpu_create(void) {
    CPU *p = malloc(sizeof *p);
    return p;
}
// method for destroying mips
void cpu_destroy(CPU *p) {
    if (p == NULL) {
        return;
    }
    free(p);
};

// read and write getters/setters for general purpose registers
uint32_t read_gpr(const CPU *p, uint8_t idx) {
    assert(idx < 32);
    if (0 == idx) {
        return 0;
    }

    return p->gpr[idx - 1];
};

void write_gpr(CPU *p, uint8_t idx, uint32_t value) {
    assert(idx < 32);
    assert(value <= 0xffffffff);
    if (0 == idx) {
        return;
    }
    p->gpr[idx - 1] = value;
};
// read hi register (32 bit value)
uint32_t read_HI(const CPU *p) { return p->hi; };

// write hi register (32 bit value)
void write_HI(CPU *p, uint32_t value) {
    p->hi = value;
};

uint32_t read_LO(const CPU *p) { return p->lo; };

void write_LO(CPU *p, uint32_t value) {
    p->lo = value;
};
// increment and get program counter
uint32_t get_pc(const CPU *p) { return p->pc; };
void increment_pc(CPU *p) {
    assert(p->pc + 4 <= 0xffffffff);
    p->pc += 4;
};
void set_pc(CPU *p, uint32_t address) {
    p->pc = address;
};
