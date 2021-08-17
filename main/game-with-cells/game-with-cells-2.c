#include <stdio.h>

int main(void)
{
    int n = 0, m = 0;
    (void)scanf("%d %d", &n, &m);
    printf("%d\n", (n + n % 2) * (m + m % 2) / 4);
    return 0;
}
