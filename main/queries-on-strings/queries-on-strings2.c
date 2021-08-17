#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#elif defined(__MINGW32__)
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#define __USE_MINGW_ANSI_STDIO 1
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif // ! _MSC_VER

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define XSTR(a) STR(a)
#define STR(a) #a

#define MAXLEN 10000

enum { alphalen = 'z' - 'a' + 1 };

static void run_all_queries(int (*const counts)[alphalen], const size_t stop)
{
    int q = 0;
    for ((void)scanf("%d", &q); q > 0; --q) {
        size_t i = 0u, j = 0u;
        (void)scanf("%zu %zu", &i, &j);
        assert(0u != i && i <= j && j < stop);
        --i;
        
        size_t distinct_count = 0u;
        for (size_t k = 0u; k != alphalen; ++k)
            if (counts[j][k] - counts[i][k] != 0) ++distinct_count;
        
        printf("%zu%c", distinct_count, (q == 1 ? '\n' : ' '));
    }
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        char str[MAXLEN + 1] = { 0 };
        (void)scanf("%" XSTR(MAXLEN) "s", str);
        const size_t stop = strlen(str) + 1u;
        
        int counts[MAXLEN + 1][alphalen] = { { 0 } };
        for (size_t i = 0u, j = 1u; j != stop; ++i, ++j) {
            const ptrdiff_t k = str[i] - (ptrdiff_t)'a';
            assert(0 <= k && k <= alphalen);

            memcpy(counts[j], counts[i], sizeof counts[i]);
            ++counts[j][k];
        }
        
        run_all_queries(counts, stop);
    }
}
