#include <stdio.h>

int main(void)
{
    int n = 0;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        for (int j = i; j < n; ++j) putchar(' ');
        for (int j = i; j > 0; --j) putchar('#');
        putchar('\n');
    }
}
