#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static inline void require(const bool condition)
{
    if (!condition) abort();
}

static inline void *xcalloc(const size_t count, const size_t size)
{
    void *const ret = calloc(count, size);
    require(ret);
    return ret;
}

static inline void destroy(int **const pp)
{
    free(*pp);
    *pp = NULL;
}

static int *read_values(const int count)
{
    int *const values = xcalloc(count, sizeof *values);
    for (int i = 0; i < count; ++i) (void)scanf("%d", &values[i]);
    return values;
}

static int comp(const void *const p, const void *const q)
{
    const int lhs = *(const int *)p, rhs = *(const int *)q;

    if (lhs < rhs) return -1;
    if (lhs > rhs) return +1;
    return 0;
}

int main(void)
{
    int count = 0, key = 0;
    (void)scanf("%d%d", &key, &count);

    int *values = read_values(count);

    const int *const pos = bsearch(&key, values, count, sizeof *values, comp);
    require(pos);
    printf("%td\n", pos - values);

    destroy(&values);
}
