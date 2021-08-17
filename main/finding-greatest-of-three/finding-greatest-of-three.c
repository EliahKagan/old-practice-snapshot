#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static inline intmax_t max2(const intmax_t m, const intmax_t n)
{
    return m > n ? m : n;
}

static inline intmax_t max3(const intmax_t a, const intmax_t b,
                                              const intmax_t c)
{
    return max2(max2(a, b), c);
}

int main(void)
{
    intmax_t a, b, c;
    while (scanf("%" SCNdMAX ",%" SCNdMAX ",%" SCNdMAX, &a, &b, &c) == 3)
        printf("%" PRIdMAX "\n", max3(a, b, c));
}
