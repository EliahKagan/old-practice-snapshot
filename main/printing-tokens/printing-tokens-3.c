#include <stdio.h>
#include <string.h>

int main(void)
{
    char *strtok_r(char *, const char *, char **);
    enum { bufsiz = 1001 };
    static const char *const ws = " \t\n\v\f\r";

    char buf[bufsiz] = {0};
    fgets(buf, bufsiz, stdin);

    for (char *pos = NULL, *tok = strtok_r(buf, ws, &pos);
            tok; tok = strtok_r(NULL, ws, &pos))
        puts(tok);
}
