#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

i32 platform_get_page_size(void);
void *reserve_memory(u64 size);
bool commit_memory(void *ptr, u64 size);
bool release_memory(void *ptr, u64 size);

#endif
