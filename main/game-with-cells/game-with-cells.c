#include <stdio.h>

int main(void)
{
    int n = 0, m = 0;
    (void)scanf("%d %d", &n, &m);
    if (n % 2) ++n;
    if (m % 2) ++m;
    printf("%d\n", n * m / 4);
    return 0;
}
