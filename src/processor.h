#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <stdint.h>

typedef struct CPU CPU;

CPU *cpu_create(void);
void cpu_destroy(CPU *p);

// read and write getters/setters for general purpose registers
uint32_t read_gpr(const CPU *p, uint8_t idx);
void write_gpr(CPU *p, uint8_t idx, uint32_t value);

// read and write hi/lo
uint32_t read_HI(const CPU *p);
void write_HI(CPU *p, uint32_t value);

uint32_t read_LO(const CPU *p);
void write_LO(CPU *p, uint32_t value);

uint32_t get_pc(const CPU *p);
void increment_pc(CPU *p);
void set_pc(CPU *p, uint32_t address);

#endif // !CPU_H
