#include <stdio.h>

static int sum_digits(int n)
{
    enum { b = 10 };
    
    int s = 0;
    for (; n != 0; n /= b) s += n % b;
    return s;
}

int main(void)
{
    int t = 0;
    for (scanf("%d", &t); t > 0; --t) {
        int n = 0;
        scanf("%d", &n);
        printf("%d\n", sum_digits(n));
    }
}
