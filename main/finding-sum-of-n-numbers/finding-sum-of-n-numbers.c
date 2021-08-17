#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

int main(void)
{
    for (int n; scanf("%d", &n) == 1; ) printf("%d\n", n * (n + 1) / 2);
}
