#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enum { nmax = 100, got_value_flag = 1 << 14, clear_flag = ~got_value_flag };

static_assert(nmax < got_value_flag, "range too big to coexist with flag");

static size_t read_size()
{
    size_t n = 0u;
    (void)scanf("%zu", &n);
    if (n == 0u || n > nmax) abort();
    return n;
}

// Reads a record of unsigned integers. This is intentional, even though input
// values may be negative. The negative values will be represented by large
// positive integers.
static void read_record(const size_t n, unsigned *const a)
{
    for (size_t i = 0u; i != n; ++i) (void)scanf("%u", &a[i]);
}

static void zero_out_large_elements(const size_t n, unsigned *const a)
{
    const unsigned len = (unsigned)n;

    for (size_t i = 0u; i != n; ++i)
        if (a[i] > len) a[i] = 0u;
}

// Write a flag to positions in the array one less than each of the values
// in the array.
static void flag_nonzero_elements(const size_t n, unsigned *const a)
{
    for (size_t i = 0u; i != n; ++i) {
        const unsigned x = a[i] & clear_flag;
        if (x != 0u) a[(size_t)(x - 1u)] |= got_value_flag;
    }
}

// Get the lowest value whose presence is indicated by a flag set by
// the flag_nonzero_elements() function.
static unsigned get_min_flagged_value(const size_t n, unsigned *const a)
{
    size_t i = 0u;
    while (i != n && (a[i] & got_value_flag)) ++i;
    return (unsigned)i + 1u;
}

// Finds and returns the smallest positive number not in the first n elements
// of a. Note: mutates (the data pointed to by) a.
static unsigned get_min_missing_positive(const size_t n, unsigned *const a)
{
    zero_out_large_elements(n, a);
    flag_nonzero_elements(n, a);
    return get_min_flagged_value(n, a);
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        unsigned a[nmax] = { 0u };
        const size_t n = read_size();
        read_record(n, a);
        
        printf("%u\n", get_min_missing_positive(n, a));
    }
}
