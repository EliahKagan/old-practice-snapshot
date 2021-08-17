#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    bool in = false;
    int ch = 0;

    do {
        ch = getchar();

        if (isspace(ch) || ch == EOF) {
            if (in) {
                in = false;
                putchar('\n');
            }
        } else {
            in = true;
            putchar(ch);
        }
    }
    while (ch != EOF);
}
