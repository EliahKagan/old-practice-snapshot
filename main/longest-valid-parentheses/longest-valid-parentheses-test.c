// Generates well-formed input for testing longest-valid-parentheses.c.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Outputs len followed by a randomized string of len '(' and ')' parentheses.
// You must call srand() before using this function.
static void emit_parens(int len)
{
    assert(len > 0);

    //printf("%d\n", len);
    while (len-- > 0) putchar("()"[rand() & 1]);
    putchar('\n');
}

int main(void)
{
    int maxlen = 10000; // emit strings this length and shorter
    int count = 1;      // emit this many strings

    assert(1 <= count && count <= maxlen);

    printf("%d\n", count);

    srand((unsigned)time(NULL));
    while (count-- > 0) emit_parens(maxlen--);

    return EXIT_SUCCESS;
}
