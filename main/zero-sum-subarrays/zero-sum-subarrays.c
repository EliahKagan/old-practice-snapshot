#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <stdio.h>

int main(void)
{
    enum { nmax = 1000 };
    
    int a[nmax + 1] = { 0 }; // partial sums
    
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        int n = 0;
        (void)scanf("%d", &n);
        assert(0 < n && n <= nmax);
        
        const int jstop = n + 1;
        for (int j = 1; j != jstop; ++j) {
            (void)scanf("%d", &a[j]);
            a[j] += a[j - 1];
        }
        
        int count = 0;
        
        for (int i = 0; i != n; ++i) {
            const int ai = a[i];
            
            for (int j = i + 1; j != jstop; ++j)
                if (ai == a[j]) ++count;
        }
        
        printf("%d\n", count);
    }
}
