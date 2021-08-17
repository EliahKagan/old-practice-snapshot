#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static long long gcd(const long long m, const long long n)
{
    return n == 0LL ? m : gcd(n, m % n);
}

static inline void positize(long long *const kp)
{
    if (*kp < 0) *kp = -*kp;
}

static inline bool is_vishesh_trimurty(long long a, long long b, long long c)
{
    if (a * a + b * b != c * c) return false;
    if (a == 0LL || b == 0LL) return true;

    positize(&a);
    positize(&b);
    positize(&c);

    return gcd(gcd(a, b), c) == 1LL;
}

int main()
{
    long long a, b, c;
    while (scanf("%lld,%lld,%lld", &a, &b, &c) == 3)
        printf("%s\n", (is_vishesh_trimurty(a, b, c) ? "YES" : "NO"));
}
