#include "../src/processor.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <criterion/redirect.h>
#include <stdint.h>
/* #include <stdio.h> */
uint out_of_bounds = 0xffffffff;

// Testing reading and writing to the registers

Test(read_write_gpr, read_write_zero) {
    CPU *test_cpu = cpu_create();
    uint32_t result = read_gpr(test_cpu, 0);
    write_gpr(test_cpu, 0, 12);
    cr_assert_eq(result, 0, "Expected $0 to be 0, but got %d", result);
    cpu_destroy(test_cpu);
}

Test(read_write_gpr, read_write_others) {
    CPU *test_cpu = cpu_create();
    for (int i = 1; i < 32; i++) {
        write_gpr(test_cpu, i, 0x1f + i);
    }
    for (int i = 1; i < 32; i++) {
        cr_assert_eq(read_gpr(test_cpu, i), 0x1f + i,
                     "failed on register $%d, expected 0x%X, got 0x%X", i,
                     0x1f + i, read_gpr(test_cpu, i));
    }

    write_gpr(test_cpu, 31, out_of_bounds);
    cr_assert_eq(read_gpr(test_cpu, 31), out_of_bounds,
                 "max 32 bit input failed");
    cpu_destroy(test_cpu);
}

Test(read_write_HI_LO, read_write) {
    CPU *test_cpu = cpu_create();

    write_LO(test_cpu, 0xff);
    cr_assert_eq(read_LO(test_cpu), 0xff,
                 "failed read and/or write LO, expected 0xff, got 0x%X",
                 read_LO(test_cpu));

    write_LO(test_cpu, out_of_bounds);
    cr_assert_eq(read_LO(test_cpu), out_of_bounds,
                 "failed to write max 32 bit value");
    write_HI(test_cpu, 0xff);
    cr_assert_eq(read_HI(test_cpu), 0xff,
                 "failed read and/or write HI, expected 0xff, got 0x%X",
                 read_HI(test_cpu));

    write_HI(test_cpu, out_of_bounds);
    cr_assert_eq(read_HI(test_cpu), out_of_bounds,
                 "failed to write max 32 bit value");

    cpu_destroy(test_cpu);
}

Test(program_counter, increment) {
    CPU *test_cpu = cpu_create();
    cr_assert_eq(0, get_pc(test_cpu), "failed get_pc, expected 0, got 0x%X",
                 get_pc(test_cpu));
    increment_pc(test_cpu);
    cr_assert_eq(4, get_pc(test_cpu), "failed get_pc, expected 4, got 0x%X",
                 get_pc(test_cpu));

    cpu_destroy(test_cpu);
}
Test(program_counter, set_pc) {
    CPU *test_cpu = cpu_create();
    cr_assert_eq(0, get_pc(test_cpu), "failed get_pc, expected 0, got 0x%X",
                 get_pc(test_cpu));
    set_pc(test_cpu, 0x1f);
    cr_assert_eq(0x1f, get_pc(test_cpu),
                 "failed get_pc, expected 0x1f, got 0x%X", get_pc(test_cpu));

    cpu_destroy(test_cpu);
}
