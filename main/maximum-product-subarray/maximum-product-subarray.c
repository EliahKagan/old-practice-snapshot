#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#define __USE_MINGW_ANSI_STDIO 1
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif // ! __MINGW32__

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int *read_record(const size_t n)
{
    int *const a = calloc(n, sizeof *a);
    if (a == NULL) abort();
    
    for (size_t i = 0u; i != n; ++i) (void)scanf("%d", &a[i]);
    return a;
}

// Helper function for max_product().
static inline long long
max_product_from(const int *const a, const size_t n, size_t i)
{
    long long best = LLONG_MIN;
    
    for (long long cur = 1LL; i != n; ++i) {
        cur *= a[i];
        if (best < cur) best = cur;
    }
    
    return best;
}

// Naive O(n**2) algorithm.
static long long max_product(const int *const a, const size_t n)
{
    long long best = LLONG_MIN;
    
    for (size_t i = 0u; i != n; ++i) {
        const long long cur = max_product_from(a, n, i);
        if (best < cur) best = cur;
    }
    
    return best;
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        size_t n = 0u;
        (void)scanf("%zu", &n);
        
        int *const a = read_record(n);
        printf("%lld\n", max_product(a, n));
        free(a);
    }
}
