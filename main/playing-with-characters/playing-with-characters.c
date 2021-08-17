#include <stdio.h>

#define STR(x) #x
#define XSTR(x) STR(x)

#define MAXLEN 4096

int main(void)
{
    char ch = '\0', s[MAXLEN + 1] = { 0 }, sen[MAXLEN + 1] = { 0 };
    scanf("%c %" XSTR(MAXLEN) "s %" XSTR(MAXLEN) "[^\n] ", &ch, s, sen);
    printf("%c\n%s\n%s\n", ch, s, sen);
    return 0;
}
