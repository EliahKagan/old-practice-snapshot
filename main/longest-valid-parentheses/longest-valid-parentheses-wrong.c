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

// depth_pos[d] will hold the leftmost (0-based) index in the string where a
// depth of exactly d was achieved, but such that no negative depth (which is
// invalid) was reached between there and the current index.
static int depth_pos[MAXLEN + 1];

static inline int max(const int x, const int y)
{
    return x > y ? x : y;
}

// Initializes a run by reading a string of parentheses into parens and
// resetting the necessary portion of depth_pos.
static void initialize(void)
{
    enum { before_left = -2, left = -1 };

    int len = 0;
    (void)scanf("%" XSTR(MAXLEN) "s%n", parens, &len);
    if (len <= 0) abort();

    while (len != 0) depth_pos[len--] = before_left;
    depth_pos[0] = left;
}

// Processes a single string of parentheses from standard input and returns the
// length of the longest valid substring (i.e., balanced and never reaching a
// negative nesting depth).
static int run(void)
{
    initialize();
    int best = 0;

    for (int depth = 0, left = -1, right = 0; parens[right] != '\0'; ++right) {
        if (parens[right] == '(')   ++depth;
        else if (depth != 0)        --depth;
        else {
            // When an unmatched ')' is encountered, the nesting depth would
            // become negative. Instead, keep it at 0 and set the left bound
            // here. Strings beginning up to this position but ending after it
            // will not be considered.
            depth_pos[0] = left = right;
            continue;
        }

        if (depth_pos[depth] < left) depth_pos[depth] = right;
        else best = max(best, right - depth_pos[depth]);
    }

    return best;
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) printf("%d\n", run());
}
