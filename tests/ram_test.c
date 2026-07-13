#include "../src/ram.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <criterion/redirect.h>
#include <signal.h> // Provides the SIGABRT constant
#include <stdint.h>
#define TEST_FILENAME "temp_test_binary.bin"

Test(ram, get_size) {
    RAM *test_ram = ram_create(0x100000); // 4 megabytes of ram
    cr_assert_eq(get_size(test_ram), 0x100000, "ram should be 4 megabytes");
    ram_destroy(test_ram);
}

Test(ram, read_write_byte) {
    RAM *test_ram = ram_create(0x10000);
    write_byte(test_ram, 0x00000, 0xff);
    write_byte(test_ram, 0x0ffff, 0xaf);
    cr_assert_eq(read_byte(test_ram, 0x00), 0xff,
                 "read byte value incorrect, expected 0xff, got 0x%x",
                 read_byte(test_ram, 0x00));
    cr_assert_eq(read_byte(test_ram, 0x0ffff), 0xaf,
                 "read byte value incorrect, expected 0xaf, got 0x%x",
                 read_byte(test_ram, 0x0ffff));
    ram_destroy(test_ram);
}

Test(ram, read_write_halfword) {
    RAM *test_ram = ram_create(0x10000);
    write_half(test_ram, 0x00000, 0xffff);
    write_half(test_ram, 0x0fffe, 0xacbf);
    cr_assert_eq(read_half(test_ram, 0x00), 0xffff,
                 "read half value incorrect, expected 0xffff, got 0x%x",
                 read_half(test_ram, 0x00));

    cr_assert_eq(read_half(test_ram, 0x0fffe), 0xacbf,
                 "read half value incorrect, expected 0xacbf, got 0x%x",
                 read_half(test_ram, 0x0fffe));

    ram_destroy(test_ram);
}

Test(ram, read_write_word) {
    RAM *test_ram = ram_create(0x10000);
    write_word(test_ram, 0x00000, 0xffffffff);
    write_word(test_ram, 0x0fffc, 0x1234abcd);
    cr_assert_eq(read_word(test_ram, 0x00), 0xffffffff,
                 "read word value incorrect, expected 0xffff, got 0x%x",
                 read_word(test_ram, 0x00));

    cr_assert_eq(read_word(test_ram, 0x0fffc), 0x1234abcd,
                 "read word value incorrect, expected 0xacbf, got 0x%x",
                 read_word(test_ram, 0x0fffc));

    ram_destroy(test_ram);
}

Test(ram, readbyte, .signal = SIGABRT) {
    RAM *test_ram = ram_create(0x10000);
    read_byte(test_ram, 0x10000);
    ram_destroy(test_ram);
}

Test(ram, writebyte, .signal = SIGABRT) {
    RAM *test_ram = ram_create(0x10000);
    write_byte(test_ram, 0x10000, 0xff);
    ram_destroy(test_ram);
}

Test(ram, readhalf_overflow, .signal = SIGABRT) {
    RAM *test_ram = ram_create(17);
    read_half(test_ram, 16);
    ram_destroy(test_ram);
}

Test(ram, writehalf_overflow, .signal = SIGABRT) {
    RAM *test_ram = ram_create(17);
    write_half(test_ram, 16, 0xff);
    ram_destroy(test_ram);
}
Test(ram, readword_overflow, .signal = SIGABRT) {
    RAM *test_ram = ram_create(15);
    read_word(test_ram, 12);
    ram_destroy(test_ram);
}

Test(ram, writeword_overflow, .signal = SIGABRT) {
    RAM *test_ram = ram_create(15);
    write_word(test_ram, 12, 0xff);
    ram_destroy(test_ram);
}
Test(ram, readhalf_alignment, .signal = SIGABRT) {
    RAM *test_ram = ram_create(16);
    read_half(test_ram, 1);
    ram_destroy(test_ram);
}
Test(ram, writehalf_alignment, .signal = SIGABRT) {
    RAM *test_ram = ram_create(16);
    write_half(test_ram, 1, 0xffff);
    ram_destroy(test_ram);
}
Test(ram, readword_alignment, .signal = SIGABRT) {
    RAM *test_ram = ram_create(16);
    read_word(test_ram, 1);
    ram_destroy(test_ram);
}
Test(ram, writeword_alignment, .signal = SIGABRT) {
    RAM *test_ram = ram_create(16);
    write_word(test_ram, 1, 0xff);
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

Test(ram_diagnostics, hex_dump_with_memstream) {
    RAM *ram = ram_create(16);
    write_word(ram, 0x00, 0x12345678);

    char *buffer = NULL;
    size_t size = 0;

    // Open an in-memory stream that writes dynamically directly to our buffer
    // string
    FILE *mem_stream = open_memstream(&buffer, &size);

    // Pass the memory stream instead of stdout
    ram_dump(mem_stream, ram, 0x00, 4);

    fclose(mem_stream); // Forces the stream to flush calculations directly into
                        // 'buffer'

    // Verify natively
    cr_assert_str_eq(
        buffer,
        "--- RAM DUMP (Start: 0x00000000, Length: 4 bytes) ---   0x00000000: "
        "78 56 34 12                                      | xV4.\n");

    free(buffer); // Clean up the memory string allocation
    ram_destroy(ram);
}
