// stack.c - fun with _alloca

#ifndef UNICODE
#define UNICODE
#endif /* UNICODE */

#ifndef _UNICODE
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#define _UNICODE
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif /* _UNICODE */

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <locale.h>
#include <malloc.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <Windows.h>

static const wchar_t *g_progname;
static jmp_buf g_jmp_buf;

static __declspec(noreturn) void die(const wchar_t *__restrict const fmt, ...)
{
    assert(fmt != NULL);

    fwprintf(stderr, L"%ls: error: ", g_progname);

    va_list v;
    va_start(v, fmt);
    vfwprintf(stderr, fmt, v);
    va_end(v);

    fputwc(L'\n', stderr);

    exit(EXIT_FAILURE);
}

static void initialize(const int argc, wchar_t **const argv)
{
    assert(argc > 0);
    g_progname = argv[0];
    if (argc != 2) die(L"too %ls arguments", (argc < 2 ? L"few" : L"many"));

    if (_wsetlocale(LC_ALL, L"") == NULL)
        fwprintf(stderr, L"%ls: warning: failure retrieving locale\n", argv[0]);
}

static inline bool big_sizes(void) // returns true if unintmax_t is size_t
{
    return (uintmax_t)SIZE_MAX == UINTMAX_MAX;
}

static inline bool is_ws(const wchar_t *const a)
{
    assert(a != NULL);

    wchar_t c;
    return swscanf_s(a, L" %lc", &c, 1u) <= 0;
}

static size_t to_size(const wchar_t *const a)
{
    assert(a != NULL);

    _set_errno(0);
    const wchar_t *end = NULL;
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif
    const uintmax_t n = wcstoumax(a, (wchar_t **)&end, 0);
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
    int e = 0;
    _get_errno(&e);

    if (!is_ws(end) || n == UINTMAX_C(0)
                    || (big_sizes() ? (n == UINTMAX_MAX && e == ERANGE)
                                    : n > (uintmax_t)SIZE_MAX))
        die(L"size argument must be an integer from 1 to %Iu", SIZE_MAX);

    return (size_t)n;
}

static PVOID xAddVectoredExceptionHandler(bool first,
                                          PVECTORED_EXCEPTION_HANDLER handler)
{
    assert(handler != NULL);

    PVOID h = AddVectoredExceptionHandler((first ? 1ul : 0ul), handler);
    if (h == NULL) die(L"can't register exception handler");
    return h;
}

static void xRemoveVectoredExceptionHandler(PVOID h)
{
    assert(h != NULL);

    if (RemoveVectoredExceptionHandler(h) == 0ul) {
        fwprintf(stderr, L"%ls: warning: can't unregister exception handler\n",
                 g_progname);
    }
}

static LONG WINAPI handle_stack_overflow(PEXCEPTION_POINTERS infop)
{
    assert(infop != NULL);

    if (infop->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
        longjmp(g_jmp_buf, 1);

    return EXCEPTION_CONTINUE_SEARCH;
}

#ifdef __GNUC__
int wmain(int, wchar_t **); // prevents "-Wmissing-prototypes" warning
#endif
int wmain(int argc, wchar_t **argv)
{
    initialize(argc, argv);

    const size_t n = to_size(argv[1]);
    wprintf(L"Attempting to allocate %Iu bytes on the stack...", n);
    fflush(stdout);

    const void *p = NULL;
    PVOID h = xAddVectoredExceptionHandler(true, handle_stack_overflow);

    if (setjmp(g_jmp_buf) == 0) p = _alloca(n);
    else if (_resetstkoflw())   p = NULL;
    else                        abort();

    xRemoveVectoredExceptionHandler(h);
    wprintf(L" %ls!\n", (p == NULL ? L"failed" : L"success"));
    return p == NULL ? EXIT_FAILURE : EXIT_SUCCESS;
}
