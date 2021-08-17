#include <stdio.h>

static void read_record(int *const a, const int n)
{
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
}

int main(void)
{
    enum { n = 3 };

    int a[n] = {0}, b[n] = {0}, alice = 0, bob = 0;

    read_record(a, n);
    read_record(b, n);

    for (int i = 0; i < n; ++i) {
        if (a[i] > b[i])        ++alice;
        else if (a[i] < b[i])   ++bob;
    }

    printf("%d %d\n", alice, bob);
}
