#include "../src/ram.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <criterion/redirect.h>
#include <signal.h> // Provides the SIGABRT constant
#include <stdint.h>
#define TEST_FILENAME "temp_test_binary.bin"

Test(get_size, get_size) {
    RAM *test_ram = ram_create(0x100000); // 4 megabytes of ram
    cr_assert_eq(get_size(test_ram), 0x100000, "ram should be 4 megabytes");
    ram_destroy(test_ram);
}

Test(read_write, read_write_byte) {
    RAM *test_ram = ram_create(0x10000);
    write_byte(test_ram, 0x00000, 0xff);
    write_byte(test_ram, 0x10000, 0xaf);
    cr_assert_eq(read_byte(test_ram, 0x00), 0xff,
                 "read byte value incorrect, expected 0xff, got 0x%x",
                 read_byte(test_ram, 0x00));
    cr_assert_eq(read_byte(test_ram, 0x10000), 0xaf,
                 "read byte value incorrect, expected 0xaf, got 0x%x",
                 read_byte(test_ram, 0x00));
    ram_destroy(test_ram);
}

Test(read_write, read_write_halfword) {
    RAM *test_ram = ram_create(0x10000);
    write_half(test_ram, 0x00000, 0xffff);
    write_half(test_ram, 0x10000 - 1, 0xacbf);
    cr_assert_eq(read_half(test_ram, 0x00), 0xffff,
                 "read half value incorrect, expected 0xffff, got 0x%x",
                 read_half(test_ram, 0x00));

    cr_assert_eq(read_half(test_ram, 0x10000), 0xacbf,
                 "read half value incorrect, expected 0xacbf, got 0x%x",
                 read_half(test_ram, 0x00));

    ram_destroy(test_ram);
}

Test(read_write, word) {
    RAM *test_ram = ram_create(0x10000);
    write_word(test_ram, 0x00000, 0xffffffff);
    write_word(test_ram, 0x10000 - 3, 0x1234abcd);
    cr_assert_eq(read_word(test_ram, 0x00), 0xffffffff,
                 "read word value incorrect, expected 0xffff, got 0x%x",
                 read_word(test_ram, 0x00));

    cr_assert_eq(read_word(test_ram, 0x10000), 0x1234abcd,
                 "read word value incorrect, expected 0xacbf, got 0x%x",
                 read_word(test_ram, 0x00));

    ram_destroy(test_ram);
}

Test(overflow, readbyte, .signal = SIGABRT) {
    RAM *test_ram = ram_create(0x10000);
    read_byte(test_ram, 0x10001);
    ram_destroy(test_ram);
}

Test(overflow, writebyte, .signal = SIGABRT) {
    RAM *test_ram = ram_create(0x10000);
    write_byte(test_ram, 0x10001, 0xff);
    ram_destroy(test_ram);
}

Test(overflow, readhalf, .signal = SIGABRT) {
    RAM *test_ram = ram_create(0x10000);
    read_half(test_ram, 0x10000);
    ram_destroy(test_ram);
}

Test(overflow, writehalf, .signal = SIGABRT) {
    RAM *test_ram = ram_create(0x10000);
    write_half(test_ram, 0x10000, 0xff);
    ram_destroy(test_ram);
}
Test(overflow, readword, .signal = SIGABRT) {
    RAM *test_ram = ram_create(0x10000);
    read_word(test_ram, 0x10000 - 2);
    ram_destroy(test_ram);
}

Test(overflow, writeword, .signal = SIGABRT) {
    RAM *test_ram = ram_create(0x10000);
    write_word(test_ram, 0x10000 - 2, 0xff);
    ram_destroy(test_ram);
}
Test(load_file, loadfile) {
    RAM *test_ram = ram_create(4096);
    uint8_t dummy_payload[4]; // our dummy payload
    dummy_payload[0] = 255;
    dummy_payload[1] = 128;
    dummy_payload[2] = 64;
    dummy_payload[3] = 32; // set up values for payload
    uint32_t offset = 0x100;
    FILE *f = fopen(TEST_FILENAME, "wb"); // writeback
    cr_assert_not_null(f, "Failed to create temporary test file asset");
    fwrite(dummy_payload, 1, 4, f);
    load_file(test_ram, TEST_FILENAME, offset);
    for (int i = 0; i < 4; i++) {
        uint8_t expected = dummy_payload[i];
        uint8_t actual = read_byte(test_ram, offset + i);

        cr_assert_eq(actual, expected,
                     "Mismatch at RAM offset %u! expected %u, got %u",
                     offset + i, expected, actual);
    }

    fclose(f);
    ram_destroy(test_ram);
}

Test(clear_ram, clearram) {
    RAM *test_ram = ram_create(4096);
    write_word(test_ram, 0, 0xabcdef12);
    cr_assert_eq(0x12, read_byte(test_ram, 0),
                 "value at memory address 0 should be 0x12");

    cr_assert_eq(0xef, read_byte(test_ram, 1),
                 "value at memory address 1 should be 0xef");

    cr_assert_eq(0xcd, read_byte(test_ram, 2),
                 "value at memory address 2 should be 0xcd");

    cr_assert_eq(0xab, read_byte(test_ram, 3),
                 "value at memory address 3 should be 0xab");
    clear_ram(test_ram);

    cr_assert_eq(0, read_byte(test_ram, 0),
                 "value at memory address 0 should be 0 after clear");

    cr_assert_eq(0, read_byte(test_ram, 1),
                 "value at memory address 1 should be 0 after clear");

    cr_assert_eq(0, read_byte(test_ram, 2),
                 "value at memory address 2 should be 0 after clear");

    cr_assert_eq(0, read_byte(test_ram, 3),
                 "value at memory address 3 should be 0 after clear");

    ram_destroy(test_ram);
}
