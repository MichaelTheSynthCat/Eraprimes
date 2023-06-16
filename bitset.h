// bitset.h
// Author: Michal Krulich
// API for fields of bits (type bitset_t)
// macros, inline functions
// use -DUSEINLINE to use the inline functions over macros

#ifndef BITSET_H_USED
#define BITSET_H_USED 1
#include <stdlib.h>
#include <assert.h>
#include "error.h"

// bit size of unsigned long
#define LONG_BITS (sizeof(unsigned long) * __CHAR_BIT__)

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

// Returns minimal needed count of unsigned long to store given number of bits.
// example: 64-bit long: bits/64 + (bits%64 + 64 - 1)/64
#define required_ul_for_bits(bits) ((unsigned long)(bits) / (LONG_BITS) + ((unsigned long)(bits) % (LONG_BITS) + LONG_BITS - 1) / (LONG_BITS))

// Creates a local bitset with the given name. The bitset can contain max n bits.
#define bitset_create(var_name, n)                                  \
  unsigned long var_name[required_ul_for_bits((n)) + 1] = {(n), 0}; \
  static_assert((n) > 0, "bitset_create: n must be bigger than 0.")

// Creates a local bitset and allocates memory space for it. Similiar behaviour as bitset_create.
#define bitset_alloc(var_name, n)                                                 \
  assert(("bitset_alloc: n must be bigger than 0.", (n) > 0));                    \
  bitset_t var_name = calloc(required_ul_for_bits(n) + 1, sizeof(unsigned long)); \
  if (var_name == NULL)                                                           \
    error_exit("bitset_alloc: memory error");                                     \
  var_name[0] = n

#ifndef USE_INLINE

// Frees memory space used by the given bitset.
#define bitset_free(var_name) free(var_name)

// Returns the number of bits the bitset can hold.
// Bit Size of the bitset is stored in the first element of the unsigned long array.
#define bitset_size(var_name) var_name[0]

// Sets bit in the bitset of var_name on the specified index to 0 or 1 based on the value of the expression parameter.
#define bitset_setbit(var_name, index, expression)                                                                                      \
  do                                                                                                                                    \
  {                                                                                                                                     \
    if ((index) >= 0 && (index) < bitset_size(var_name))                                                                                \
      var_name[(index) / (LONG_BITS) + 1ul] = (expression) ? ((1ul << (index) % (LONG_BITS)) | var_name[(index) / (LONG_BITS) + 1ul])   \
                                                           : ((~1ul << (index) % (LONG_BITS)) & var_name[(index) / (LONG_BITS) + 1ul]); \
    else                                                                                                                                \
      error_exit("bitset_getbit: Index %lu out of range 0..%lu", (unsigned long)(index), bitset_size(var_name) - 1);                    \
  } while (0);

// Returns bit in the bitset of var_name on the specified index.
#define bitset_getbit(var_name, index) (((index) >= 0 && (index) < bitset_size(var_name)) ? (((1ul << ((bitset_index_t)(index) % (LONG_BITS))) & var_name[(bitset_index_t)(index) / (LONG_BITS) + 1ul]) ? 1 : 0) \
                                                                                          : (error_exit("bitset_getbit: Index %lu out of range 0..%lu", (unsigned long)(index), bitset_size(var_name) - 1), 0))

#endif // #ifndef USE_INLINE

#ifdef USE_INLINE

inline void bitset_free(bitset_t var_name)
{
  free(var_name);
}
inline bitset_index_t bitset_size(bitset_t var_name) { return var_name[0]; }
inline void bitset_setbit(bitset_t var_name, bitset_index_t index, unsigned expression)
{
  if (index < bitset_size(var_name))
    var_name[(index) / (LONG_BITS) + 1ul] = (expression) ? ((1ul << (index) % (LONG_BITS)) | var_name[(index) / (LONG_BITS) + 1ul])
                                                         : ((~1ul << (index) % (LONG_BITS)) & var_name[(index) / (LONG_BITS) + 1ul]);
  else
    error_exit("bitset_getbit: Index %lu out of range 0..%lu", (unsigned long)(index), bitset_size(var_name) - 1);
}
inline unsigned long bitset_getbit(bitset_t var_name, bitset_index_t index)
{
  if (index >= bitset_size(var_name))
  {
    error_exit("bitset_getbit: Index %lu out of range 0..%lu", (unsigned long)(index), bitset_size(var_name) - 1);
  }
  return (((1ul << index % (LONG_BITS)) & var_name[index / (LONG_BITS) + 1]) ? 1 : 0);
}

#endif // #ifdef USE_INLINE

#endif // #ifndef BITSET_H_USED
