#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

int main() {
    enum { nmax = 100 };
    
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        int n = 0;
        (void)scanf("%d", &n);
        if (n <= 0 || n > nmax) abort();
        
        int a[nmax] = { 0 };
        for (int i = 0; i != n; ++i) (void)scanf("%d", &a[i]);
        
        int acc = 0;
        for (int i = 0; i != n - 1; ++i)
            for (int j = i + 1; j != n; ++j) acc += a[i] * a[j];
        
        printf("%d\n", acc);
    }
}
