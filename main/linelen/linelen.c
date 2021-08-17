/* linelen.c - count the number of characters per line in a file, sans '\n' */

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* make sure _Noreturn is defined */
#if !(defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L /* C11 */)
#ifdef __GNUC__
#define _Noreturn __attribute__ ((noreturn))
#elif defined(MSC_VER)
#define _Noreturn __declspec(noreturn)
#else
#define _Noreturn
#endif
#endif /* !C11 */

static const char *g_progname;

static _Noreturn void outerr(void);
static void xflush(void);
static void xprintf(const char *fmt, ...);
int main(int argc, const char *const *argv);

void outerr(void)
{
    fflush(stdout);
    fprintf(stderr, "%s: error: couldn't write to standard output\n",
            g_progname);
    exit(EXIT_FAILURE);
}

void xflush(void)
{
    if (fflush(stdout)) outerr();
}

void xprintf(const char *fmt, ...)
{
    va_list v;
    assert(fmt != NULL);

    va_start(v, fmt);
    if (vprintf(fmt, v) < 0) outerr();
    va_end(v);
}

int main(int argc, const char *const *argv)
{
    FILE *fp;
    register unsigned long pos;
    register int c;
    
    g_progname = argv[0];
    atexit(xflush);
    
    /* check number of arguments */
    if (argc > 2) {
        fprintf(stderr, "%s: warning: too many arguments, all but the 1st "
                        "ignored\n", g_progname);
    }
    else if (argc == 1) {
        fprintf(stderr, "%s: error: too few arguments\n", g_progname);
        fprintf(stderr, "%s: usage:  %s <filename>\n", g_progname, argv[0]);
        return EXIT_FAILURE;
    }
    
    /* open file */
    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: error: unable to open file \"%s\"\n",
                g_progname, argv[1]);
        return EXIT_FAILURE;
    }
    
    /* loop through lines printing numbers of characters */
    for (; ; xprintf("%lu\n", pos)) {
        for (pos = 0; (c = getc(fp)) != '\n'; ++pos) {
            if (c == EOF) {
                if (feof(fp)) {
                    if (pos != 0) xprintf("%lu (no line termination)\n", pos);
                    return EXIT_SUCCESS;
                }
                else if (ferror(fp)) {
                    fprintf(stderr, "%s: error: failure while reading file\n", 
                            g_progname);
                    return EXIT_FAILURE;
                }
            }
        }
    }
}
