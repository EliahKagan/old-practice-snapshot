#include <stdio.h>

enum { base = 10 };

static int sum_digits(int n)
{    
    int s = 0;
    for (; n != 0; n /= base) s += n % base;
    return s;
}

static int ank_yog(int n)
{
    while (n >= base) n = sum_digits(n);
    return n == 0 ? base - 1 : n;
}

int main(void)
{
    int t = 0;
    for (scanf("%d", &t); t > 0; --t) {
        int n = 0;
        scanf("%d", &n);
        printf("%d\n", ank_yog(n));
    }
}
