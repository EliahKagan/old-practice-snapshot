#include <stdio.h>

static inline int min(const int x, const int y)
{
    return y < x ? y : x;
}

static inline int min4(const int w, const int x, const int y, const int z)
{
    return min(min(w, x), min(y, z));
}

int main(void)
{
    int n = 0;
    (void)scanf("%d", &n);

    const int s = n * 2 - 1;

    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j)
            printf("%d ", n - min4(i, s - 1 - i, j, s - 1 - j));

        putchar('\n');
    }
}
