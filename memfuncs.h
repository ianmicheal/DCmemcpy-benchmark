//==============================================================================
//  SH4 Memory Functions: Main Header
//==============================================================================
//
// This file provides function prototypes for memmove, memcpy, memset, and memcmp,
// which are required by GCC when used in a freestanding environment.
//
// NOTE:
// If you need to move/copy memory between overlapping regions, use memmove instead of memcpy.
//

#ifndef __MEMFUNCS_H_
#define __MEMFUNCS_H_

// In freestanding mode, the only available standard header files are: <float.h>,
// <iso646.h>, <limits.h>, <stdarg.h>, <stdbool.h>, <stddef.h>, and <stdint.h>
// (C99 standard 4.6).

#include <stddef.h>
#include <stdint.h>

//
// USAGE INFORMATION:
//
// The "len" argument is "# of x bytes to move," e.g. memmove_32bit needs to
// know "how many multiples of 32 bit (4 bytes) to move." All functions with len
// follow the same pattern, e.g. memset_16bit needs to know how many multiples
// of 2 bytes to set, so a len of 4 tells it to set 8 bytes.
//
// IMPORTANT NOTE:
// Please ensure that destination and source buffers are aligned appropriately
// (1, 2, 4, or 8 bytes depending on the function). Your program may crash if not
// (actually, the functions *will* crash unless you get lucky). So
// __attribute__((aligned(*size*))) is very useful here!
// ...And, just to be clear, 1-byte alignment is the same as unaligned. ;)
//
// Caches and 64-Bit NOTE:
// The 64-bit functions only show a benefit in copy-back/write-back memory areas,
// as accesses outside the operand cache are split up into 32-bit transfers. So
// when used on write-through areas, the 64-bit functions behave no faster than
// their 32-bit counterparts. It is also worth noting that all functions are faster
// in copy-back areas (including the overhead from cache block purging right after!).
// By default, DreamHAL sets P0/P3/U0 to write-back/copy-back, and P1 to write-
// through in startup.S. As such, the AND mask 0x1fffffff comes in handy here.
//



void * memcpyasm (void *dest, const void *src, size_t len);
void * memcpy_16bit(void *dest, const void *src, size_t len);
void * memcpy_32bit(void *dest, const void *src, size_t len);
void * memcpy_32bit_16Bytes(void *dest, const void *src, size_t len); // 16 bytes, 4-byte alignmnet
void * memcpy_64bit(void *dest, const void *src, size_t len);
void * memcpy_64bit_32Bytes(void *dest, const void *src, size_t len); // 32 bytes, 8-byte alignment
// NOTE: Store Queues are better, though they require 32-byte alignment.

void * memmoveasm (void *dest, const void *src, size_t len);
void * memmove_16bit(void *dest, const void *src, size_t len);
void * memmove_32bit(void *dest, const void *src, size_t len);
void * memmove_64bit(void *dest, const void *src, size_t len); // There is a way :)


#endif /* __MEMFUNCS_H_ */
