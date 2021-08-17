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
#include <stdio.h>
#include <string.h>

#define XSTR(a) STR(a)
#define STR(a) #a

#define MAXLEN 100000

static size_t longest_prefix_suffix(const char *const str)
{
    const size_t len = strlen(str);
    assert(len != 0u);

    for (size_t jmin = 1u; jmin != len; ++jmin) {
        size_t i = 0u;
        for (size_t j = jmin; j != len && str[i] == str[j]; ++j) ++i;
        if (jmin + i == len) return i;
    }

    return 0u;
}

int main(void)
{
    char buf[MAXLEN + 1];

    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        (void)scanf("%" XSTR(MAXLEN) "s", buf);
        printf("%zu\n", longest_prefix_suffix(buf));
    }
}
