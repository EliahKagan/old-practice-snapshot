#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static_assert(sizeof(int) * CHAR_BIT >= 32, "need 32-bit or wider integers");

static int xor_sum(const int n, const int *a)
{
    enum { high_bit = 0x80000000 };
    
    int half_sum = 0;
    
    for (int mask = 1; mask != high_bit; mask <<= 1) {
        int count = 0;
        
        for (int i = 0; i != n; ++i)
            if (a[i] & mask) ++count;
        
        half_sum += (n - count) * count;
    }
    
    return half_sum * 2;
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        int n = 0;
        (void)scanf("%d", &n);
        if (n <= 0) abort();

        int a[n];
        for (int i = 0; i != n; ++i)
            if (scanf("%u", &a[i]) != 1) abort();

        printf("%d\n", xor_sum(n, a));
    }
}
