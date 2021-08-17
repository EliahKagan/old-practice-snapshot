#include <stdio.h>
#include <stdlib.h>

void update(int *const a, int *const b) {
    const int sum = *a + *b;
    const int absolute_difference = abs(*a - *b);
    *a = sum;
    *b = absolute_difference;
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;

    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}
