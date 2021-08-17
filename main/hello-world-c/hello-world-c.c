#include <stdio.h>

#define STR(a) #a
#define XSTR(a) STR(a)

#define MAXLEN 99

int main(void)
{
    char s[MAXLEN + 1];
    scanf("%" XSTR(MAXLEN) "[^\n] ", s);

    printf("Hello, World!\n%s\n", s);
    return 0;
}
