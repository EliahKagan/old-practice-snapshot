#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n = 0;
    scanf("%d", &n);
    if (n <= 0) return EXIT_FAILURE;

    double tot = n;
    int pos = 0, neg = 0, zer = 0;

    while (n-- != 0) {
        int elem = 0;
        scanf("%d", &elem);
        
        if (elem == 0)      ++zer;
        else if (elem < 0)  ++neg;
        else                ++pos;
    }

    const int p = 6;
    printf("%.*f\n%.*f\n%.*f\n", p, pos / tot, p, neg / tot, p, zer / tot);
    return EXIT_SUCCESS;
}
