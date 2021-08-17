#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#define ARRAY_LENGTH(a) (sizeof a / sizeof a[0])

#define HIGH_BIT 0x8000000000000000uLL

static int count_moves_in_game(unsigned long long n)
{
    assert(n != 0uLL);
    
    __auto_type k = 0;
    
    for (; __builtin_popcountll(n) != 1; ++k)
        n -= HIGH_BIT >> __builtin_clzll(n); // subtract next lowest power of 2
    
    return k + __builtin_ctzll(n); // count each division by 2 (to get to 1)
}

int main(void)
{
    assert(__builtin_types_compatible_p(unsigned long long, uint64_t));
    
    const char* players[] = { "Richard", "Louise" };
    
    __auto_type t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        __auto_type n = 0uLL;
        (void)scanf("%llu", &n);
        puts(players[count_moves_in_game(n) % ARRAY_LENGTH(players)]);
    }
}
