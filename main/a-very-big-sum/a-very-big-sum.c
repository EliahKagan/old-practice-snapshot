#include <stdio.h>

int main(void)
{
    long long sum = 0;

    int n = 0;
    for (scanf("%d", &n); n > 0; --n) {
        long long elem = 0;
        scanf("%lld", &elem);
        sum += elem;
    }

    printf("%lld\n", sum);
}
