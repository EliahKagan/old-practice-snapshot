#include <stdio.h>

static int popcount(int n)
{
    int count = 0;
    for (; n != 0; n >>= 1) count += (n & 1);
    return count;
}

int main(void)
{
    int t = 0;
    for (scanf("%d", &t); t > 0; --t) {
        int n = 0;
        scanf("%d", &n);
        printf("%d\n", popcount(n));
    }
}
