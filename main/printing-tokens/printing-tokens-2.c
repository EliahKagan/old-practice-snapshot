#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    bool in = false;
    int ch = 0;

    do {
        ch = getchar();

        if (!isspace(ch) && ch != EOF) {
            in = true;
            putchar(ch);
        }
        else if (in) {
            in = false;
            putchar('\n');
        }
    }
    while (ch != EOF);
}
