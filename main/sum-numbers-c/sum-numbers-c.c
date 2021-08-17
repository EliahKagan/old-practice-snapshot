#include <stdio.h>

int main(void)
{
    int m = 0, n = 0;
    float x = 0.0f, y = 0.0f;
    scanf("%d%d%f%f", &m, &n, &x, &y);
    printf("%d %d\n%.1f %.1f\n", m + n, m - n, x + y, x - y);
    return 0;
}
