#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define FMT_SCN "%" SCNdFAST64
#define FMT_PRI "%" PRIdFAST64

static int_fast64_t gcd(const int_fast64_t m, const int_fast64_t n)
{
    return n == 0 ? m : gcd(n, m % n);
}

static inline int_fast64_t absval(const int_fast64_t k)
{
    return k < 0 ? -k : k;
}

int main(void)
{
    int t = 0;
    int_fast64_t m = 0, n = 0;
    
    for ((void)scanf("%d", &t); t > 0; --t) {
        (void)scanf(FMT_SCN " " FMT_SCN, &m, &n);
        printf(FMT_PRI "\n", absval(gcd(m, n)));
    }
}
