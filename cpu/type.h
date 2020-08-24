#ifndef TYPE_H
#define TYPE_H

/* Instead of using 'chars' to allocate non-character bytes,
 * we will use these new type with no semantic meaning */

#include <stdint.h>

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#endif