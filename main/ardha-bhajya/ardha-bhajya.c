#ifdef NDEBUG
#undef NDEBUG
#endif

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#ifdef __GNUC__
#define ATTRIBUTE(x) __attribute__ (x)
#else
#define ATTRIBUTE(x)
#endif

ATTRIBUTE ((malloc, returns_nonnull))
static void *xcalloc(const size_t count, const size_t size)
{
    void *const p = calloc(count, size);
    if (p == NULL) abort(); // TODO: consider quitting with diagnostic instead
    return p;
}

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wbad-function-cast"
#endif
ATTRIBUTE ((always_inline, const))
static inline uint32_t sqrt32(const uint32_t n)
{
    return (uint32_t)sqrt(n);
}

ATTRIBUTE ((always_inline, const))
static inline size_t sqrt32_to_size(const uint32_t n)
{
    return (size_t)sqrt(n);
}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

ATTRIBUTE ((nonnull, returns_nonnull))
static bool *raw_sieve(const uint32_t max)
{
    assert(1u < max && max < UINT32_MAX);

    const size_t imax = sqrt32_to_size(max), jmax = max;
    
    // false means not marked as composite
    bool *const a = xcalloc(jmax + 1u, sizeof *a);

    for (size_t i = 3u; i <= imax; i += 2u) {
        if (!a[i]) {
            const size_t jstep = i * 2u;
            for (size_t j = i * i; j <= jmax; j += jstep) a[j] = true;
        }
    }

    return a;
}

ATTRIBUTE ((returns_nonnull))
static uint32_t *sieve(const uint32_t max, const size_t size)
{
    assert(1u < max && max < UINT32_MAX && size != 0u);

    bool *const a = raw_sieve(max);
    uint32_t *const primes = xcalloc(size, sizeof *primes);

    primes[0] = 2u;
    size_t i = 1u;

    const size_t jmax = (size_t)max;
    for (size_t j = 3u; j <= jmax; j += 2) {
        if (!a[j]) {
            assert(i != size);
            primes[i++] = (uint32_t)j;
        }
    }

    assert(i == size); // array should be just big enough
    free(a);
    return primes;
}

ATTRIBUTE ((nonnull, pure))
static bool is_semiprime(const uint32_t *primes, const ptrdiff_t size,
                         uint32_t n)
{
    assert(size > 0);
    if (n == 0u) return false;

    enum { target = 2 }; // number of divisors for a number to be semiprime
    int count = 0;

    for (; (n & 1u) == 0u; n >>= 1u) ++count; // quickly divide out factors of 2
    if (count > target) return false;
    if (n == 1u) return count == target;

    const uint32_t bound = sqrt32(n);
    const uint32_t *const end = primes + size;

    while (++primes != end && *primes <= bound) { // already checked 1st prime
        while (n % *primes == 0u) {
            if (++count > target) return false;
            if ((n /= *primes) == 1u) return count == target;
        }
    }

    return ++count == target; // n > 1u here, so it's the final prime factor
}

int main(void)
{
    enum { max = 65536 }; // (int)sqrt(UINT32_MAX)
    enum { size = 6542 }; // pi(max)

    uint32_t *const primes = sieve(max, (size_t)size);

    int t = 0;
    for (scanf("%d", &t); t > 0; --t) {
        uint32_t n = 0;
        (void)scanf("%" SCNu32, &n);
        puts(is_semiprime(primes, size, n) ? "YES" : "NO");
    }

    free(primes);
}
