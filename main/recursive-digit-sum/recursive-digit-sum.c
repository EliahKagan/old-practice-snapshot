#include <ctype.h>
#include <stdio.h>

enum { base = 10 };

static long long sum_digits(long long n)
{    
    long long s = 0LL;
    for (; n != 0LL; n /= base) s += n % base;
    return s;
}

static long long ank_yog(long long n)
{
    while (n >= base) n = sum_digits(n);
    return n == 0LL ? base - 1LL : n;
}

int main(void)
{
    scanf(" ");
    
    long long n = 0LL;
    for (int d; isdigit(d = getchar()); ) n += d - '0';
    
    long long k = 0LL;
    scanf("%lld", &k);
    
    printf("%lld\n", ank_yog(n * k));
}
