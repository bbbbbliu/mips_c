#include "processor.h"
#include <stdbool.h>
#include <stdint.h>
// #include <stdio.h>
#include <stdlib.h>

struct CPU {
  /* General Purpose Registers
   * Не забудь:
   * $0 всегда возвращает 0!
   * $31 (називается $ra, return address) есть обратный адрес
   * */
  uint32_t gpr[32];

  /* Multiply/Divide */
  uint32_t hi;
  uint32_t lo;

  /* Program Counters*/
  uint32_t pc;
  // uint32_t pc_next; /* необязательный для branch-delay */
};

CPU *cpu_create(void) {
  CPU *p = malloc(sizeof *p);
  return p;
}

void cpu_destroy(CPU *p) {
  if (p == NULL) {
    return;
  }
  free(p);
};
