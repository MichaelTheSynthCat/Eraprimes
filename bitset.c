// bitset.c
// Author: Michal Krulich
// This file servers only for purpose of use of inline functions over bitfields.

#define USE_INLINE
#include "bitset.h"

extern inline void bitset_free(bitset_t jmeno_pole);
extern inline bitset_index_t bitset_size(bitset_t jmeno_pole);
extern inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, unsigned vyraz);
extern inline unsigned long bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);
