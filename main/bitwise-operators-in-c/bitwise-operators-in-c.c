#include <limits.h>
#include <stdio.h>

static void calculate_the_maximum(const int n, const int k)
{
    int conj = INT_MIN, disj = INT_MIN, xdisj = INT_MIN;

    for (int x = 1; x < n; ++x) {
        for (int y = x + 1; y <= n; ++y) {
            if (conj < (x & y) && (x & y) < k) conj = x & y;
            if (disj < (x | y) && (x | y) < k) disj = x | y;
            if (xdisj < (x ^ y) && (x ^ y) < k) xdisj = x ^ y;
        }
    }

    printf("%d\n%d\n%d\n", conj, disj, xdisj);
}

int main(void)
{
    int n, k;
    (void)scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);
}
