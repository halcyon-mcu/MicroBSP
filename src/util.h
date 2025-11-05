#pragma once

#define set(ty, addr, to) *((volatile ty *)(addr)) = to

#define get(ty, addr) *((volatile ty *)(addr))

#define setbit(ty, addr, pos, to)                                              \
  set(ty, addr, (get(ty, addr) & ~(1 << pos)) | ((to & 1) << pos))
