#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

static int popcount(uintmax_t k)
{
#ifdef __GNUC__
    if (k <= UINT_MAX) return __builtin_popcount((unsigned)k);
#elif defined(_MSC_VER)
    if (k <= UINT_MAX) return __popcnt((unsigned)k);
#endif

    int count = 0;
    for (; k != 0u; k >>= 1u) count += (k & 1u);
    return count;
}

static void run(int n)
{
    uintmax_t odds = 0u, even_nonpowers = 0u, even_powers = 0u; // sums

    while (n-- > 0) {
        uintmax_t k = 0;
        (void)scanf("%" SCNuMAX, &k);
        
        if (k & 1u) odds += k;
        else if (popcount(k) == 1) even_powers += k;
        else even_nonpowers += k;
    }

    printf("%" PRIuMAX " %" PRIuMAX " %" PRIuMAX "\n",
            odds, even_nonpowers, even_powers);
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        int n = 0;
        (void)scanf("%d", &n);
        run(n);
    }
}
