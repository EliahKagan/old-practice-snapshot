#include <stdio.h>

int main(void)
{
    int t = 0;
    for (scanf("%d", &t); t > 0; --t) {
        int n = 0;
        scanf("%d", &n);
        printf("%d\n", __builtin_popcount(n));
    }
}
