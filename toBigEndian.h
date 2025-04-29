#ifndef __TOBIGENDIAN_H
#define __TOBIGENDIAN_H

#include <stdint.h>

// Detect system endianness at runtime
static int is_little_endian(void) {
    uint16_t x = 1;
    return *((uint8_t*)&x) == 1;
}

// Swap byte order of a 32-bit integer
static uint32_t swap_endian32(uint32_t val) {
    return ((val >> 24) & 0x000000FF) |
           ((val >> 8)  & 0x0000FF00) |
           ((val << 8)  & 0x00FF0000) |
           ((val << 24) & 0xFF000000);
}

// Convert to big endian if needed
static uint32_t to_big_endian32(uint32_t val) {
    return is_little_endian() ? swap_endian32(val) : val;
}

#endif