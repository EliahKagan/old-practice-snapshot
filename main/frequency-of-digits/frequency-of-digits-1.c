#include <assert.h>
#include <ctype.h>
#include <stdio.h>

int main(void)
{
    enum { base = 10 };
    static_assert('9' - '0' + 1 == base, "digit arithmetic");
    int freqs[base] = {0};

    for (int ch = 0; isalnum(ch = getchar()); )
        if ('0' <= ch && ch <= '9') ++freqs[ch - '0'];

    const char *sep = "";
    for (int i = 0; i < base; ++i) {
        printf("%s%d", sep, freqs[i]);
        sep = " ";
    }

    putchar('\n');
}
