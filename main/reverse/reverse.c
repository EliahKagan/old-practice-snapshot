// reverse.c - demonstration of function to reverse a string

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline char *end(char *const a)
{
    return strchr(a, '\0');
}

static inline void swap(char *const p, char *const q)
{
    const char c = *p;
    *p = *q;
    *q = c;
}

static char *reverse(char *const a)
{
    char *q = end(a);
    if (q != a)
        for (char *p = a; p < --q; ++p) swap(p, q);
    
    return a;
}

int main(int argc, char *argv[])
{
    return argc > 1 && puts(reverse(argv[1])) >= 0 ? EXIT_SUCCESS
                                                   : EXIT_FAILURE;
}
