#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

#define XSTR(a) STR(a)
#define STR(a) #a

// Maxlen should be 10**8, but G4G won't let me malloc() that much, so I'm
// using 10**7 instead and hoping that's enough. If not, the program will
// parse a new text operand each time the buffer is full, and thus behave
// erratically (and give wrong answers that are hard to debug), but it
// should still not have undefined behavior.
#define MAXLEN 10000000
#define FMTSPEC "%" XSTR(MAXLEN) "s"

const char *g_progname;

static void die(const char* const msg)
{
    fprintf(stderr, "%s: error: %s\n", g_progname, msg);
    exit(EXIT_FAILURE);
}

static void check_charset(void)
{
    const char *a = "abcdefghijklmnopqrstuvwxyz";
    for (char c = 'a'; c == *a; ++c) ++a;
    if (*a != '\0') die("lower-case letters are not represented contiguously");
}

static void *xmalloc(const size_t size)
{
    void *const p = malloc(size);
    if (p == NULL) die("out of memory");
    return p;
}

static inline int lex(const char **const tokp) // consumes a single token
{
    const int c = (*tokp)[0];

    if (c < 'n') { // got a token before "n", keep the character set's code
        ++*tokp;
        return c;
    }
    else if (c != 'n') { // got a token after "ng", bump code one higher
        ++*tokp;
        return c + 1;
    }
    else if ((*tokp)[1] == 'g') {  // got the "ng" token, bump code one higher
        *tokp += 2;
        return c + 1;
    } else { // got the "n" token, keep the character set's code
        ++*tokp;
        return c;
    }
}

static int compare(const char *lhs, const char *rhs)
{
    while (*lhs != '\0' && *rhs != '\0') {
        const int left = lex(&lhs), right = lex(&rhs);
        if (left != right) return left < right ? -1 : 1;
    }

    if (*lhs == *rhs) return 0;     // same length
    return *lhs == '\0' ? -1 : 1;   // the shorter string is less
}

int main(int argc, char **argv)
{
    (void)argc;
	g_progname = argv[0];
    check_charset();
	char *const lhs = xmalloc(MAXLEN + 1), *const rhs = xmalloc(MAXLEN + 1);

	int t = 0;
	for ((void)scanf("%d", &t); t > 0; --t) {
        if (scanf(FMTSPEC FMTSPEC, lhs, rhs) != 2)
            die("couldn't read two string operands for comparison");

        printf("%d\n", compare(lhs, rhs));
	}

	free(rhs);
	free(lhs);
}
