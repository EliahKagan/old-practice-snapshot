// rep.c - repeat a string several (perhaps many) times

#ifdef __ICL // Intel compiler on Windows
#define _CRT_SECURE_NO_WARNINGS // for strerror()
#define noreturn _Noreturn      // Microsoft headers lack <stdnoreturn.h>
#pragma warning suppress 1419
noreturn void exit(int);
#else
#include <stdnoreturn.h>
#endif

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __MINGW32__
#include <stdint.h>
#if LLONG_MIN == INT64_MIN && LLONG_MAX == INT64_MAX
#include <inttypes.h>
#define LLFMT "%" PRId64 // probably "%I64d"
#define SPECIAL_LLFMT
#endif
#endif // ! __MINGW32__

#ifndef LLFMT
#define LLFMT "%lld"
#endif

#if defined(__GNUC__) || defined(__clang__)
#define ATTRIBUTE(x) __attribute__ (x)
#else
#define ATTRIBUTE(x)
#endif

#define NOMSG "\n"

typedef enum tagStatus {
    kStatusGood,
    kStatusBadIO,
    kStatusBadArgs
} Status;

static const char *g_progname = "";

ATTRIBUTE ((format(printf, 2, 0), nonnull))
static noreturn void vdie(const Status s, const char *restrict const fmt,
                          va_list v)
{
    assert((s == kStatusGood) == (strcmp(fmt, NOMSG) == 0));

    if (s != kStatusGood) {
        fprintf(stderr, "%s: error: ", g_progname);
        vfprintf(stderr, fmt, v);
        fputc('\n', stderr);
    }
    
    exit(s);
}

ATTRIBUTE ((format(printf, 2, 3), nonnull))
static noreturn void die(const Status s, const char *restrict const fmt, ...)
{
    va_list v;
    va_start(v, fmt);
    vdie(s, fmt, v);
    va_end(v);
}

#ifndef SPECIAL_LLFMT // in this program we only use LLFMT with arg_die
ATTRIBUTE ((format(printf, 1, 2)))
#endif
ATTRIBUTE ((nonnull))
static noreturn void arg_die(const char *restrict fmt, ...)
{
    va_list v;
    va_start(v, fmt);
#if defined(SPECIAL_LLFMT) && defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"
#endif
    vdie(kStatusBadArgs, fmt, v);
#if defined(SPECIAL_LLFMT) && defined(__clang__)
#pragma clang diagnostic pop
#endif
    va_end(v);
}

ATTRIBUTE ((nonnull))
static noreturn void nan_die(const char *arg)
{
    arg_die("count \"%s\" is not a number", arg);
}

ATTRIBUTE ((nonnull))
static char *skip_whitespace(char *str)
{
    while (isspace((unsigned char)*str)) ++str;
    return str;
}

ATTRIBUTE ((nonnull))
static char *rtrim(char *str) // trims whitespace from the end of str
{
    char *p = strchr(str, '\0');
    while (p > str && isspace((unsigned char)p[-1])) --p;
    *p = '\0';
    return str;
}

ATTRIBUTE ((nonnull))  // returns count arg, sets *strp to string-to-repeat arg
static char *read_args(int argc, char *argv[], char **const strp)
{
    if (argc > 0) g_progname = argv[0];
    --argc, ++argv;
    
    if (argc != 2) {
        if (argc < 1)
            arg_die("got 0 args (need 2: count, and string to repeat)");
        
        if (argc == 1) arg_die("got 1 arg, need 2nd (for string to repeat)");
        
        arg_die("got %d args (need just 2: count, and string to repeat)",
                argc);
    }

    *strp = argv[1];
    return argv[0];
}

ATTRIBUTE ((nonnull))   // validates that arg has no non-whitespace after end
static void check_extraneous(char *arg, char *end)
{
    assert(arg <= end);
    char *new_end = skip_whitespace(end); // -V102 // -V647 [false alarm:
    if (*new_end == '\0') return;         // skip_whitespace() returns char *]
    
    ptrdiff_t len = (end >= arg ? end - arg : 0);
    if (len > INT_MAX) len = INT_MAX;
    
    if (len == 0) nan_die(arg);
    
    arg_die("\"%.*s\" looks like a number, but what's \"%s\"?",
            (int)len, arg, rtrim(new_end));
}

ATTRIBUTE ((nonnull))
static bool plausible_zero(const char *expr)
{
    if (*expr == '+' || *expr == '-') ++expr;
    if (*expr != '0') return false;
    
    if (*++expr == 'x' || *expr == 'X') {
        if (*++expr != '0') return false;
        ++expr;
    }
    
    for (; *expr != '\0'; ++expr)
        if (*expr != '0') return false;
    
    return true;
}

ATTRIBUTE ((nonnull))
static void check_count(const long long count, const int strtoll_errno,
                        const char *const arg)
{
    if (count < 0LL) {
        if (strtoll_errno == ERANGE)
            arg_die("negative count \"%s\" not allowed", arg);
        
        arg_die("negative count " LLFMT " not allowed", count);
    }
    
    if (strtoll_errno == ERANGE)
        arg_die("count \"%s\" > " LLFMT " (max)", arg, (long long)LLONG_MAX);
    
    if (count == 0LL && !plausible_zero(arg)) nan_die(arg);
}

ATTRIBUTE ((nonnull))
static long long parse_count(char *arg)
{
    arg = skip_whitespace(arg);
    
    errno = 0;
    char *end = NULL;
    long long count = strtoll(arg, &end, 0);
    const int e = errno;
    
    check_extraneous(arg, end);
    *end = '\0'; // trim str's trailing whitespace
    check_count(count, e, arg);
    
    return count;
}

int main(int argc, char *argv[])
{
    char *a = NULL;
    long long n = parse_count(read_args(argc, argv, &a));
    
    for (; n != 0LL; --n) {
        errno = 0;
        if (fputs(a, stdout) < 0) break;
    }
    
    if (n == 0LL) {
        errno = 0;
        if (fflush(stdout) == 0) die(kStatusGood, NOMSG);
    }
    
    die(kStatusBadIO, "write failed: %s", strerror(errno));
}
