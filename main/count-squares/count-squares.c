#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

static uint_fast64_t isqrt(const uint_fast64_t n)
{
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wbad-function-cast"
#endif
    uint_fast64_t r = (uint_fast64_t)sqrtl((long double)n);
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
    while (r * r < n) ++r;
    while (r * r > n) --r;
    return r;
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        uint_fast64_t n = 0u;
        (void)scanf("%" SCNuFAST64, &n);
        printf("%" PRIuFAST64 "\n", isqrt(n - 1u));
    }
}
