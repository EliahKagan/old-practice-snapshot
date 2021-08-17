#include <stdio.h>
#include <stdlib.h>

static void update(int *a, int *b) {
    int old_a = *a, old_b = *b;
    *a = old_a + old_b;
    *b = abs(old_a - old_b);
}

// FIXME for unit test scaffolding: Consider printing a final newline and
// ensuring no possible input causes unitialized variables to be read.
int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}
