#include <ctype.h>
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

static int get_ank_yog(void)
{
    scanf(" ");
    
    int n = 0;
    for (int d; isdigit(d = getchar()); ) n += d - '0';
    return ank_yog(n);
}

int main(void)
{
    int t = 0;
    for (scanf("%d", &t); t > 0; --t) printf("%d\n", get_ank_yog());
}
