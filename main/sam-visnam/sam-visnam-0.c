#include <stdio.h>

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        int n = 0;
        (void)scanf("%d", &n);
        printf("%d\n", !(n % 2));
    }
    
    return 0;
}
