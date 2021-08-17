#include <stdio.h>

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        int n = 0, acc = 0, x = 0;
        
        for ((void)scanf("%d", &n); n > 0; --n) {
            (void)scanf("%d", &x);
            acc ^= x;
        }
        
        printf("%d\n", acc);
    }
    
    return 0;
}
