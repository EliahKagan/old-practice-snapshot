#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        int ans = 0, n = 0, k = 0;

        for ((void)scanf("%d", &n); n > 0; --n) {
            (void)scanf("%d", &k);
            ans ^= k;
        }

        printf("%d\n", ans);
    }

    return 0;
}
