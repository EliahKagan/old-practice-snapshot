// euler12b.c - Project Euler problem 12: Highly divisible triangular number
//              Even more optimized version (in C, this time).
//
// To build:  icl /Qstd=c99 /W5 /Wp64 /O3 /QxHost euler12b.c /DTHRESHOLD=480
// That runs a long while, then prints:  76576500 has 576 divisors.

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef THRESHOLD
#define THRESHOLD 500
#endif

typedef uint_fast32_t Number;
#define FMTSPEC PRIuFAST32

int main(void)
{
    for (Number n = 0, i = 1; ; ++i) {
        n += i; // n is the ith triangular number

        Number factors = 1; // one, for n itself (not covered below)
        for (Number over_half = n / 2 + 1, k = 1; k != over_half; ++k)
            if (n % k == 0) ++factors;

        if (factors > THRESHOLD) {
            printf("%" FMTSPEC " has %" FMTSPEC " divisors.\n", n, factors);
            return EXIT_SUCCESS;
        }
    }
}
