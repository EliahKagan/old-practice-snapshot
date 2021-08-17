#include <stdio.h>

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        int n = 0, m = 0;
        (void)scanf("%d %d", &n, &m);
        printf("%d\n", (--m > 31 ? 0 : n >> m));
    }
}
