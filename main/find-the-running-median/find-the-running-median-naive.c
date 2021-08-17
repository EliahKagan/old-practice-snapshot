#include <limits.h>
#include <stdio.h>

int main(void)
{
    int n = 0;
    (void)scanf("%d", &n);
    int a[n + 1];
    a[0] = INT_MIN;

    for (int e = 0, i = 0; i != n; ) {
        (void)scanf("%d", &e);
        int k = i + 1;
        for (int j = i; e < a[j]; ) a[k--] = a[j--];
        a[k] = e;

        const int mid = ++i / 2;

        if (i % 2 == 0) {
            const int m = a[mid] + a[mid + 1];
            printf("%d.%c\n", m / 2, (m % 2 == 0 ? '0' : '5'));
        }
        else printf("%d.0\n", a[mid + 1]);
    }
}
