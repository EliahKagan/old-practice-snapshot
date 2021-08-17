// wwc.c - simple Windows word count utility, demonstrating error codes raised
//         for file open (and read) operations (can be compiled as C99 or C++)
//
//          -= Suggested Build Commands (listed by compiler vendor) =-
// Microsoft (C):   cl /RTCcsu /W4 wwc.c
// Microsoft (C++): cl /TP /RTCcsu /W4 wwc.c
// Intel (C):       icl /Qstd=c99 /RTCcsu /W5 /Wp64 wwc.c
// Intel (C++):     icl /TP /Qstd=c++11 /RTCcsu /Wp64 wwc.c

#define UNICODE
#define _UNICODE
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_STDIO_ISO_WIDE_SPECIFIERS

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h> // for _T()
#include <wchar.h>
#include <wctype.h>

#if defined(__cplusplus) || __STDC_VERSION__ < 199901L
#if defined(_MSC_VER) || defined(__GNUC__)
#define restrict __restrict
#else
#define restrict
#endif
#endif

#if defined(__ICL) && defined(__cplusplus)
#define NONSTANDARD_SIGNATURE(...) _Pragma("warning push") \
        _Pragma("warning disable 2553") (__VA_ARGS__) _Pragma("warning pop")
#else
#define NONSTANDARD_SIGNATURE(...) (__VA_ARGS__)
#endif

static const wchar_t *g_progname;
static int g_status = EXIT_SUCCESS;

static void msg(const wchar_t *restrict const fmt, ...)
{
    assert(fmt != NULL);
    
    fwprintf(stderr, L"%ls: ", g_progname);
    
    va_list v;
    va_start(v, fmt);
    vfwprintf(stderr, fmt, v);
    va_end(v);
    
    putwc(L'\n', stderr);
    
    g_status = EXIT_FAILURE;
}

static FILE *open_file(const wchar_t *const path)
{
    assert(path != NULL);
    
    _set_errno(0);
    FILE *const fp = _wfopen(path, L"r");
    
    if (fp == NULL) {
        int e = 0;
        _get_errno(&e);
        msg(L"couldn't open \"%ls\": %ls (error #%d)", path, _wcserror(e), e);
    }
    
    return fp;
}

static bool really_eof(FILE *restrict const fp,
                       const wchar_t *restrict const path)
{
    assert(fp != NULL && path != NULL);

    if (ferror(fp)) {
        int e = 0;
        _get_errno(&e);
        msg(L"%ls: read error: %ls (error #%d)", path, _wcserror(e), e);
    }
    else if (!feof(fp)) return false;

    return true;
}

static size_t word_count(FILE *restrict const fp,
                         const wchar_t *restrict const path)
{
    assert(fp != NULL && path != NULL);
    
    size_t n = 0u;
    for (bool in_word = false; ; ) {
        _set_errno(0);
        const wint_t c = _getwc_nolock(fp);
        if (c == WEOF && really_eof(fp, path)) return n;
        
        if (iswspace(c))
            in_word = false;
        else if (!in_word) {
            in_word = true;
            ++n;
        }
    }
}

static void print_word_count(const wchar_t *const path)
{
    assert(path != NULL);
    
    FILE *const fp = open_file(path);
    if (fp == NULL) return;
    
    const size_t n = word_count(fp, path);
    wprintf(L"%ls: %zu word%ls\n", path, n, (n == 1 ? L"" : L"s"));
    
    _fclose_nolock(fp);
}

int wmain NONSTANDARD_SIGNATURE(int argc, wchar_t **argv)
{
    assert(argc > 0); // should hold, Windows supports cmdline args
    g_progname = argv[0];
    
    if (argc < 2)
        print_word_count(_T(__FILE__));
    else
        while (*++argv != NULL) print_word_count(*argv);
    
    return g_status;
}
