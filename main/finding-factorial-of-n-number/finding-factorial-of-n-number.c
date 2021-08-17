#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uintmax_t factorial(uintmax_t n)
{
    uintmax_t acc = 1u;
    while (n > 1u) acc *= n--;
    return acc;
}

int main(void)
{
    uintmax_t n;
    while (scanf("%" SCNuMAX, &n) == 1)
        printf("%" PRIuMAX "\n", factorial(n));
}
