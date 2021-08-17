// vectored.c - registering and using a vectored exception handler in Windows

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
#include <malloc.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <Windows.h>

static const size_t k_size = 1000000000ul;
static const wchar_t *g_progname;
static jmp_buf g_jmp_buf;

static LONG WINAPI handle_stack_overflow(PEXCEPTION_POINTERS infop)
{
    if (infop->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
        longjmp(g_jmp_buf, 1);

    return EXCEPTION_CONTINUE_SEARCH;
}

static int try_alloc(const size_t size)
{
    if (setjmp(g_jmp_buf) != 0) {
        fwprintf(stderr, L"%ls: error: can't allocate %Iu bytes\n",
                 g_progname, k_size);
        return EXIT_FAILURE;
    }

    const void *const p = _alloca(size);
    wprintf(L"%Iu byes allocated successfully at %p.\n", k_size, p);
    return EXIT_SUCCESS;
}

#ifdef __MINGW32__
int wmain(int, wchar_t **);
#endif
int wmain(int argc, wchar_t **argv)
{
    assert(argc > 0);
    g_progname = argv[0];

    PVOID h = AddVectoredExceptionHandler(true, handle_stack_overflow);
    if (h == NULL) {
        fwprintf(stderr, L"%ls: error: can't register exception handler\n",
                 g_progname);
        return EXIT_FAILURE;
    }

    const int status = try_alloc(k_size);

    if (!RemoveVectoredExceptionHandler(h)) {
        fwprintf(stderr, L"%ls: warning: can't unregister exception handler\n",
                 g_progname);
    }

    return status;
}
