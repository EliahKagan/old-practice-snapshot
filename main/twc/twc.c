/* twc.c - trivial wc implementation (c.f. K&R 2d sec.1.5.2 p.22) */
/* prints number of lines, words, and bytes provided via stdin */

#include <stdio.h>
#include <stdlib.h>

/* Make sure bool, true, and false are defined. */
#if defined(__STDC_VERSION) && __STDC_VERSION__ >= 199901L /* C99 */
#include <stdbool.h>
#endif /* __STDC_VERSION__ >= 199901L */
#if !defined(__bool_true_false_are_defined) && !defined(__cplusplus)
#ifndef false
#define false 0
#endif
#ifndef true
#define true (!false)
#endif
#ifndef bool
typedef int bool;
#endif
#endif /* !defined(__bool_true_false_are_defined) && !defined(__cplusplus) */

int main(int argc, const char *const *argv);

int main(int argc, const char *const *argv)
{
    register int c;
    unsigned long lines = 0L, words = 0L;
    register unsigned long bytes = 0L;
    register bool in = false, newline = false;
    bool fail;

    for (; (c = getchar()) != EOF; ++bytes) {
        if (c == '\n') {
            newline = true;
            ++lines;
        }
        else newline = false;
        
        if (c == ' ' || c == '\t' || newline) in = false;
        else if (!in) {
            in = true;
            ++words;
        }
    }

    fail = (bool)ferror(stdin);
    
    if (!newline && !fail) ++lines;

    if (printf("lines:\t%lu\nwords:\t%lu\nbytes:\t%lu\n", lines, words, bytes)
                    < 0) {
        fprintf(stderr, "%s: error: failure writing to standard output\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (fail) {
        fprintf(stderr, "%s: warning: failure reading from standard input\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
