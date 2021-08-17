#include <stdio.h>

#define BASE 10LL

int main(void)
{
    int t = 0;
    long long n = 0LL;
    
    for ((void)scanf("%d", &t); t > 0; --t) {
        (void)scanf("%lld", &n);
        
        long long p = BASE;
        while (p <= n) p *= BASE;
        printf("%lld\n", p - n);
    }
}
