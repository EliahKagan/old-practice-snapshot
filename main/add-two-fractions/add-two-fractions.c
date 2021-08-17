#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <stdio.h>

struct fraction {
    int numerator, denominator;
};

static int gcd(const int m, const int n)
{
    return n == 0 ? m : gcd(n, m % n);
}

static struct fraction fraction_get(void)
{
    struct fraction ret = { 0, 0 };
    (void)scanf("%d %d", &ret.numerator, &ret.denominator);
    assert(ret.denominator != 0);
    return ret;
}

static void fraction_put(const struct fraction x)
{
    printf("%d/%d\n", x.numerator, x.denominator);
}

static inline void fraction_reduce(struct fraction *const p)
{
    const int d = gcd(p->numerator, p->denominator);
    assert(d != 0);
    
    p->numerator /= d;
    p->denominator /= d;
}

static struct fraction fraction_add(const struct fraction x,
                                    const struct fraction y)
{
    struct fraction sum = {
            x.numerator * y.denominator + y.numerator * x.denominator,
            x.denominator * y.denominator
    };
    
    fraction_reduce(&sum);
    return sum;
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t)
        fraction_put(fraction_add(fraction_get(), fraction_get()));
}
