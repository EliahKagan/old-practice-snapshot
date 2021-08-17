#include <stdio.h>
#include <stdlib.h>

static int read_row_contribution(const int n, const int i)
{
    int contrib = 0;

    const int j = n - i - 1;
    for (int k = 0; k < n; ++k) {
        int elem = 0;
        (void)scanf("%d", &elem);

        if (k == i) contrib += elem;
        if (k == j) contrib -= elem;
    }

    return contrib;
}

static int read_diagonal_difference(const int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i) sum += read_row_contribution(n, i);
    return sum;
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        int n = 0;
        scanf("%d", &n);
        printf("%d\n", abs(read_diagonal_difference(n)));
    }
}
