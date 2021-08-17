#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int t = 0;
    for (scanf("%d", &t); t > 0; --t) {
        long long n = 0LL, m = 0LL;
        scanf("%lld %lld", &n, &m);
        
        lldiv_t d = lldiv(n, m);
        printf("%lld\n", (d.quot * (m - 1LL) * m + d.rem * (d.rem + 1LL)) / 2LL);
    }
}
