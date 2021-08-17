#include <limits.h>
#include <stdio.h>

static int read_max_product(int n)
{
    int acc = 1, max_neg = INT_MIN;
    
    while (n-- > 0) {
        int x = 0;
        (void)scanf("%d", &x);
        
        if (x != 0) {
            if (x < 0 && max_neg < x) max_neg = x;
            acc *= x;
            printf("(%d)\n", acc);
        }
    }
    
    if (acc < 0) acc /= max_neg;
    return acc;
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        int n = 0;
        (void)scanf("%d", &n);
        
        printf("%d\n", read_max_product(n));
    }
}
