// eraprimes.c
// Author: Michal Krulich
// The main program.
// See README.md for usage description.

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "bitset.h"

#define MAX_NUMBERS 1000000ul
#define PRINT_PRIMES 10

/* The sieve of Eratosthenes.
 * The fisrt parameter is the bitset, where the sieve is performed.
 * The result of this function is a modified bitset where n-th bit of the bitset (use bitset_getbit)
 * represents, whether n is a prime number.
 * 0 means n is a prime number while 1 is not.
 */
void Eratosthenes(bitset_t bset)
{
    bitset_setbit(bset, 0ul, 1);
    bitset_setbit(bset, 1ul, 1);
    bitset_index_t limit = sqrtl(bitset_size(bset));
    for (bitset_index_t i = 0; i <= limit; i++)
    {
        if (bitset_getbit(bset, i) == 0)
        {
            for (bitset_index_t j = 2ul; i * j < bitset_size(bset); j++)
            {
                bitset_setbit(bset, i * j, 1);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    unsigned long max_limit = MAX_NUMBERS;
    int processed_args = 1;
    unsigned long tmp;
    bool only_last = false, stats = false;
    while (processed_args < argc)
    {
        if (!strcmp(argv[processed_args], "-l"))
        {
            only_last = true;
        }
        else if (!strcmp(argv[processed_args], "-s"))
        {
            stats = true;
        }
        else if (sscanf(argv[processed_args], "%lu", &tmp) == 1)
        {
            max_limit = tmp;
        }
        else
        {
            warning("Invalid argument: %s", argv[processed_args]);
        }
        processed_args++;
    }
    bitset_alloc(bit_array, max_limit);
    clock_t start;
    start = clock();
    Eratosthenes(bit_array);
    double time_required = (double)(clock() - start) / CLOCKS_PER_SEC;
    if (only_last)
    {
        unsigned long last_primes[PRINT_PRIMES] = {
            0,
        };
        int found = 0;
        for (bitset_index_t i = max_limit - 1; i > 0; i--)
        {
            if (bitset_getbit(bit_array, i) == 0)
            {
                last_primes[found] = i;
                found++;
                if (found == PRINT_PRIMES)
                {
                    break;
                }
            }
        }
        for (int i = 0; i < PRINT_PRIMES; i++)
        {
            if (last_primes[i] != 0)
                printf("%lu\n", last_primes[i]);
        }
    }
    else
    {
        for (bitset_index_t i = 0; i < max_limit; i++)
        {
            if (bitset_getbit(bit_array, i) == 0)
            {
                printf("%lu\n", i);
            }
        }
    }
    if (stats)
        fprintf(stderr, "Time=%.3g\n", time_required);
}