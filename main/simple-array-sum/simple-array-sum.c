#include <stdio.h>

int main(void)
{
    int sum = 0;

    int n = 0;
    for (scanf("%d", &n); n > 0; --n) {
        int elem = 0;
        scanf("%d", &elem);
        sum += elem;
    }

    printf("%d\n", sum);
}
