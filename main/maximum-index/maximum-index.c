#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#elif defined(__MINGW32__)
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

static ptrdiff_t max_increasing_displacement(const int *const a,
                                             const ptrdiff_t n)
{
    assert(a != NULL && n > 0);
    
    for (ptrdiff_t margin = 1, d = n - 1; ; ++margin, --d) {
        for (ptrdiff_t i = 0; i != margin; ++i)
            if (a[i] <= a[i + d]) return d;
    }
}

int main(void)
{
    enum { nmax = 1000 };
    
    int a[nmax] = { 0 };
    
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        ptrdiff_t n = 0;
        (void)scanf("%td", &n);
        assert(n < nmax);
        
        for (ptrdiff_t i = 0; i != n; ++i) (void)scanf("%d", a + i);
        printf("%td\n", max_increasing_displacement(a, n));
    }
}
