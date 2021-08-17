#include <stdio.h>

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        unsigned long long m = 0uLL, n = 0uLL;
        (void)scanf("%llu%llu", &m, &n);
        printf("%llu\n", m / n);
    }
}
