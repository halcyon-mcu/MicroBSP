#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#define set(ty, addr, to) *((volatile ty*)(uintptr_t)(addr)) = to
#define get(ty, addr) *((volatile ty*)(uintptr_t)(addr))

#define STATIC_ASSERT(cond, msg) typedef char static_assertion_##msg[(cond) ? 1 : -1]

void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* dest, int src, size_t n);

#ifdef __cplusplus
}
#endif
