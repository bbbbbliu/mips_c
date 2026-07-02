#include "../src/processor.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <criterion/redirect.h>
#include <signal.h>
#include <stdint.h>
/* #include <stdio.h> */

// Testing reading and writing out of bounds for GPR
Test(read_write_gpr, read_out_of_bounds_index, .signal = SIGABRT) {
    CPU *test_cpu = cpu_create();
    read_gpr(test_cpu, 32);
    cpu_destroy(test_cpu);
}

Test(read_write_gpr, write_out_of_bounds_index, .signal = SIGABRT) {
    CPU *test_cpu = cpu_create();
    write_gpr(test_cpu, 32, 32);
    cpu_destroy(test_cpu);
}

Test(read_write_gpr, write_out_of_bounds_value, .signal = SIGABRT) {
    CPU *test_cpu = cpu_create();
    write_gpr(test_cpu, 31, 0x100);
    cpu_destroy(test_cpu);
}

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
    cpu_destroy(test_cpu);
}

Test(read_write_HI_LO, write_HI_out_of_bounds, .signal = SIGABRT) {
    CPU *test_cpu = cpu_create();
    write_HI(test_cpu, 0x100);
    cpu_destroy(test_cpu);
}

Test(read_write_HI_LO, write_LO_out_of_bounds, .signal = SIGABRT) {
    CPU *test_cpu = cpu_create();
    write_LO(test_cpu, 0x100);
    cpu_destroy(test_cpu);
}

Test(read_write_HI_LO, read_write, .signal = SIGABRT) {
    CPU *test_cpu = cpu_create();

    write_LO(test_cpu, 0xff);
    cr_assert_eq(read_LO(test_cpu), 0xff, "failed read and/or write LO, expected 0xff, got 0x%X", read_LO(test_cpu));

    write_HI(test_cpu, 0xff);
    cr_assert_eq(read_HI(test_cpu), 0xff, "failed read and/or write HI, expected 0xff, got 0x%X", read_HI(test_cpu));

    cpu_destroy(test_cpu);
}
