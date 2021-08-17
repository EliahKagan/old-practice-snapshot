#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <math.h>
#include <stdio.h>

static inline int isqrt(const int n)
{
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wbad-function-cast"
#endif
    return (int)sqrt(n);
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
}

static int sum_proper_divisors(const int n)
{
    if (n < 3) return n - 1;

    int stop = isqrt(n), sum = 1;
    if (stop * stop == n) sum += stop;
    else ++stop;

    for (int i = 2; i != stop; ++i)
        if (n % i == 0) sum += i + n / i;

    return sum;
}

int main(void)
{
    int n;
    (void)scanf("%d", &n); // we don't need t
    while (scanf("%d", &n) == 1) printf("%d\n", sum_proper_divisors(n));
}
