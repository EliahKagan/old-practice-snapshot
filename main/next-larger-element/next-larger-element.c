#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <stdio.h>

enum { no_element = -1 };

enum { nmax = 1000 };

int main()
{
    int a[nmax] = { 0 };
    
    int t = 0;
    for (scanf("%d", &t); t > 0; --t) {
        int n = 0;
        scanf("%d", &n);
        assert(n > 0);
        
        const int *end = a + n;
        for (int *p = a; p != end; ++p) scanf("%d", p);
        
        const int *back = end - 1;
        for (int *p = a; p != back; ++p) {
            int *q = p + 1;
            while (q != end && *p >= *q) ++q;
            
            printf("%d ", (q == end ? no_element : *q));
        }
        
        printf("%d\n", no_element);
    }
}
