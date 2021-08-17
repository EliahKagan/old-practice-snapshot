#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#elif defined(__MINGW32__)
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#define __USE_MINGW_ANSI_STDIO 1
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif // ! __MINGW32__

#include <stdio.h>
#include <stdlib.h>

#define STR(x) #x
#define XSTR(x) STR(x)

#define MAX_DIGITS 1000000

static void *xcalloc(const size_t num, const size_t size)
{
    void *const p = calloc(num, size);
    if (p == NULL) abort();
    return p;
}

static long long atoll_mod(const char *a, const long long mod)
{
    enum { base = 10 };

    long long acc = 0LL;
    while (*a != '\0') acc = (*a++ - '0' + acc * base) % mod;
    return acc;
}

static long long ipow_mod(const long long base, const int exponent,
                          const long long mod)
{
    if (exponent == 0) return 1LL;

    const long long r = ipow_mod(base, exponent / 2, mod), s = r * r;
    return (exponent % 2 == 0 ? s : s * base) % mod;
}

int main(void)
{
    char *const a = xcalloc(MAX_DIGITS + 1u, sizeof *a);

    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        int b = 0;
        long long m = 0LL;

        (void)scanf("%" XSTR(MAX_DIGITS) "s %d %lld", a, &b, &m);
        printf("%lld\n", ipow_mod(atoll_mod(a, m), b, m));
    }

    free(a);
}
