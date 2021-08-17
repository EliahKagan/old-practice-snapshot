#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

enum { mod = 10000000000 };

static __int128 modpow(const __int128 b, const int e)
{
    if (e < 2) return e == 0 ? 1 : b;
    
    __auto_type r = modpow(b, e / 2);
    r *= r;
    if (e % 2 != 0) r *= b;
    
    return r % mod;
}

static int_fast64_t compute_self_power_sum(int n)
{
    int_fast64_t sum = 0;
    
    for (; n != 0; --n)
        if (n % 10 != 0) sum += (int_fast64_t)modpow(n , n);
    
    return sum % mod;
}

int main(void)
{
    __auto_type n = 0;
    (void)scanf("%d", &n);
    printf("%" PRIdFAST64 "\n", compute_self_power_sum(n));
}
