#pragma once

#include <stdint.h>
#include <stddef.h>

#define set(ty, addr, to) *((volatile ty *)(uintptr_t)(addr)) = to

#define get(ty, addr) *((volatile ty *)(uintptr_t)(addr))

// SAFETY: This can only be used on memory that is read/write.
// Need to be careful for memory that only supports writes such as clear apis.
// For those cases, just using set() will be simpler regardless.
#define setbit(ty, addr, pos, to)                                              \
  set(ty, addr, (get(ty, addr) & ~(1 << pos)) | ((to & 1) << pos))

void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* dest, int src, size_t n);
