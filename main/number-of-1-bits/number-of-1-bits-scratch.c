//gcc 5.4.0

#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

int hammingWeight(uint32_t n) {
    _Static_assert(sizeof(unsigned) == sizeof(uint32_t)
                   && UINT_MAX == UINT32_MAX,
                   "uint32_t may not be compatible with unsigned int");

    return __builtin_popcount(n);
}

int main(void)
{
    printf("%d\n", hammingWeight(2237u));
}
