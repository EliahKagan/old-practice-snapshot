#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

__attribute__((always_inline))
static inline bool quick_sqrt_fails(const uint32_t n)
{
    return (uint32_t)sqrt(n) != (uint32_t)lroundl(floorl(sqrtl(n)));
}

__attribute__((always_inline))
static inline void test_quick_sqrt(const uint32_t n, int *const wrongp)
{
    if (quick_sqrt_fails(n)) {
        printf("%" PRIu32 "\n", n);
        ++(*wrongp);
    }
}

int main(void)
{
    int wrong = 0;
    for (uint32_t i = 0; i != UINT_MAX; ++i) test_quick_sqrt(i, &wrong);
    test_quick_sqrt(UINT_MAX, &wrong);
    printf("Count of inaccurate computed roots: %d\n", wrong);
}
