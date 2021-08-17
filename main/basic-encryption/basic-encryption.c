#include <stdio.h>

int main(void)
{
    unsigned a, b;
    while (scanf("%u %u", &a, &b) == 2)
        printf("%d\n", __builtin_popcount(a ^ b));
}
