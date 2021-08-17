#include <stdio.h>

int main() 
{
    int a = 0, b = 0;
    for ((void)scanf("%d%d", &a, &b); a <= b; ++a) {
        switch (a) {
        case 1:
            puts("one");
            break;
        case 2:
            puts("two");
            break;
        case 3:
            puts("three");
            break;
        case 4:
            puts("four");
            break;
        case 5:
            puts("five");
            break;
        case 6:
            puts("six");
            break;
        case 7:
            puts("seven");
            break;
        case 8:
            puts("eight");
            break;
        case 9:
            puts("nine");
            break;
        default:
            if (a > 9) puts(a % 2 == 0 ? "even" : "odd");
        }
    }
}

