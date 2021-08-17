#include <stdio.h>

int main(void)
{
    int n = 0;
    (void)scanf("%d", &n);
    
    int acc = 0;
    for (int i = 5; i != 0; --i) {
        acc += n % 10;
        n /= 10;
    }
    
    printf("%d\n", acc);
}
