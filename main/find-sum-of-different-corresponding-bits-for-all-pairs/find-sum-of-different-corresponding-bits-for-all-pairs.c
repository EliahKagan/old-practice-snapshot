#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static_assert(sizeof(unsigned) * CHAR_BIT >= 32,
              "need 32-bit or wider integers");

#define SIGN_MASK 0x7FFFFFFFu

static int xor_sum(const int n, const unsigned *a)
{
    int sum = 0;

    for (int j = 1; j != n; ++j)
        for (int i = 0; i != j; ++i) sum += __builtin_popcount(a[i] ^ a[j]);

    return sum * 2;
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        int n = 0;
        (void)scanf("%d", &n);
        if (n <= 0) abort();

        unsigned a[n]; // we will store both signed and unsigned as unsigned
        for (int i = 0; i != n; ++i) {
            if (scanf("%u", &a[i]) != 1) abort();
            a[i] &= SIGN_MASK;
        }

        printf("%d\n", xor_sum(n, a));
    }
}
