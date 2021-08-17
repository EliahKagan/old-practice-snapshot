#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef max
#undef max
#endif

#define XSTR(a) STR(a)
#define STR(a) #a

#define MAXLEN 10000

// The string of parentheses read from standard input for parsing.
static char parens[MAXLEN + 1];

// The stack of left-parenthesis indices encountered but not yet match.
static int left_indices[MAXLEN];

static inline int max(const int x, const int y)
{
    return x > y ? x : y;
}

// Initializes a run by reading a string of parentheses into parens.
static void initialize(void)
{
    int len = 0;
    (void)scanf("%" XSTR(MAXLEN) "s%n", parens, &len);
    if (len <= 0) abort();
}

// Processes a single string of parentheses from standard input and returns the
// length of the longest valid substring (i.e., balanced and never reaching a
// negative nesting depth).
static int run(void)
{
    initialize();
    int best = 0, cur = 0, *p = left_indices;

    for (int i = 0; parens[i] != '\0'; ++i) {
        if (parens[i] == '(')       *p++ = i;
        else if (p != left_indices) cur += i - *--p + 1;
        else {
            best = max(best, cur);
            cur = 0; // no concatenation across an unmatched ')'
        }

        printf("i=%d, parens[i] = %c, best=%d, cur=%d\n", i, parens[i], best, cur);
    }

    return max(best, cur);
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) printf("%d\n", run());
}
