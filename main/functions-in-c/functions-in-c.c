#include <stdio.h>

static int max_of_four(const int a, const int b, const int c, const int d)
{
    int acc = a;
    if (acc < b) acc = b;
    if (acc < c) acc = c;
    if (acc < d) acc = d;
    return acc;
}

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int ans = max_of_four(a, b, c, d);
    printf("%d", ans);

    return 0;
}
