// tg.c - C11 user-defined type-generic min and max macros for a few types

#if defined(__GNUC__) || defined(__clang__)
#define ATTRIBUTE(x) __attribute__ (x)
#else
#define ATTRIBUTE(x)
#endif

#ifdef _WIN32
#define NOMINMAX
#define SZFMT L"%Iu"
#else
#define SZFMT L"%zu"
#endif

#include <wchar.h>
#include <stddef.h>
#include <stdint.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) _Generic((a), int: min, size_t: minz)((a), (b))
#define max(a, b) _Generic((a), int: max, size_t: maxz)((a), (b))
#define MAGMA ATTRIBUTE ((const)) static inline
#define DEFINE_MAGMA(f, T, F) MAGMA T f(T x, T y) { return F((x), (y)); }
DEFINE_MAGMA((min), int, MIN) DEFINE_MAGMA(minz, size_t, MIN) // generic min()
DEFINE_MAGMA((max), int, MAX) DEFINE_MAGMA(maxz, size_t, MAX) // generic max()

int main()
{
    wprintf(L"max(" SZFMT L", " SZFMT L") = " SZFMT L"\n",
            (size_t)SIZE_MAX, (size_t)37, max((size_t)SIZE_MAX, (size_t)37));
}
