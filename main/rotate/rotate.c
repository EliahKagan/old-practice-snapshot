// rotate.c - simple(ish) C11 program to rotate points in a coordinate plane

#ifdef __ICL // we support Intel compiler on Windows, which uses MS headers
#define _CRT_SECURE_NO_WARNINGS
#define noreturn _Noreturn    // Microsoft headers lack <stdnoreturn.h>
#pragma warning suppress 1419
noreturn void exit(int);
#define complex _Complex      // Microsoft <complex.h> isn't C99/C11-conforming
#else
#include <stdnoreturn.h>
#include <complex.h>
#endif

#ifndef CMPLX // some implementations (e.g., MinGW) lack CMPLX() due to a bug
#define CMPLX(re, im) ((re) + (double complex)_Complex_I * (im))
#endif

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>

#if defined(__GNUC__) || defined(__clang__) // use GNU attributes if supported
#define ATTRIBUTE(x) __attribute__(x)
#else
#define ATTRIBUTE(x)
#endif

typedef struct tagRotation { double complex focus, phase; } Rotation;

static const char *g_progname = "";

#define SEP_PRIMARY    ","      // must contain _exactly_ one character
#define SEP_ALTERNATES ";"      // must contain _at least_ one character
static const char *g_separators = SEP_PRIMARY SEP_ALTERNATES;

static void apply_locale(void)
{
    setlocale(LC_ALL, "");
    
    if (localeconv()->decimal_point[0] == SEP_PRIMARY[0])
        g_separators = SEP_ALTERNATES;
}

static inline bool is_sep(const char c)
{
    return strchr(g_separators, (unsigned char)c) != NULL;
}

ATTRIBUTE ((format(printf, 1, 0), nonnull))
static noreturn void vdie(const char *restrict const fmt, va_list v)
{
    fprintf(stderr, "%s: ", g_progname);
    vfprintf(stderr, fmt, v);
    fputc('\n', stderr);
    
    exit(EXIT_FAILURE);
}

#define CALL_VDIE() do { \
        va_list v; va_start(v, fmt); vdie(fmt, v); va_end(v); } while (false)

ATTRIBUTE ((format(printf, 1, 2), nonnull))
static noreturn void die(const char *restrict const fmt, ...)
{
    CALL_VDIE();
}

ATTRIBUTE ((format(printf, 2, 3), nonnull(2)))
static noreturn void free_die(void *const p,
                              const char *restrict const fmt, ...)
{
    free(p);
    CALL_VDIE();
}

ATTRIBUTE ((nonnull))
static void grow_buffer(char **const pp, int *const sizep)
{
    enum { alloc_step = 32 };
    
    if (INT_MAX - *sizep < alloc_step)
        free_die(*pp, "error: input line too long (max=%d)", INT_MAX);
    
    char *const q = realloc(*pp, (size_t)(*sizep += alloc_step));
    if (q == NULL) free_die(*pp, "error: out of memory while reading input");
    
    *pp = q;
}

static char *get_line(void)
{
    char *p = NULL;
    
    int size = 0, pos = 0;
    do {
        grow_buffer(&p, &size);
        
        errno = 0;
        if (fgets(p + pos, size - pos, stdin) == NULL) {
            if (ferror(stdin)) free_die(p, "error: %s", strerror(errno));
            p[pos] = '\0';
            break;
        }
        
        char *const end = strchr(p + pos, '\n');
        if (end != NULL) {
            *end = '\0';
            break;
        }
        
#if defined(__ICC) || defined(__ICL)
#pragma warning suppress 2259 // OK, grow_buffer() ensures size will fit in int
#endif
        pos += (int)strlen(p + pos);
    }
    while (pos == size - 1);
    
    return p;
}

ATTRIBUTE ((nonnull))
static Rotation get_rotation(const int argc, char **const argv)
{
    if (argc > 0) g_progname = argv[0];
    if (!(argc == 2 || argc == 4))
        die("usage: %s <angle> [<focus-x-coord> <focus-y-coord>]", g_progname);
    
    Rotation rot = {CMPLX(0., 0.), exp(CMPLX(0., strtod(argv[1], NULL)))};
    if (argc == 4)
        rot.focus = CMPLX(strtod(argv[2], NULL), strtod(argv[3], NULL));
    
    return rot;
}

ATTRIBUTE ((nonnull, pure))
static inline double complex rotate(const Rotation *const rotp,
                                    const double complex point)
{
    return (point - rotp->focus) * rotp->phase + rotp->focus;
}

ATTRIBUTE ((nonnull, pure))
static const char *skip_whitespace(const char *str)
{
    while (isspace((unsigned char)*str)) ++str;
    return str;
}

static double complex get_point(void)
{
    char *const line = get_line();
    const char *const record = skip_whitespace(line); // -V102 // -V647
    
    if (*record == '\0') { // blank line indicates end-of-input
        free(line);
        exit(EXIT_SUCCESS);
    }
    
    double re = 0., im = 0.;
    char sep = '\0', extra = '\0';
    const int got = sscanf(record, "%lf %1c %lf %1c", &re, &sep, &im, &extra);
    
    free(line);
    
    if (got == 3 && is_sep(sep)) return CMPLX(re, im);
    die("error: bad input (need \"<x-coord>%c <y-coord>\")", g_separators[0]);
}

static inline void put_point(const double complex point)
{
    printf("%g%c %g\n", creal(point), g_separators[0], cimag(point));
}

int main(int argc, char *argv[])
{
    apply_locale();
    const Rotation rot = get_rotation(argc, argv);
    for (; ; ) put_point(rotate(&rot, get_point()));
}
