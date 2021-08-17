#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define XSTR(a) STR(a)
#define STR(a) #a

#define MAXLEN 100

static bool is_palindrome(const char *const a, ptrdiff_t n)
{
    for (ptrdiff_t i = 0; i < --n; ++i)
        if (a[i] != a[n]) return false;
    
    return true;
}

int main(void)
{
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        ptrdiff_t n = 0;
        char buf[MAXLEN + 1] = { 0 };
        
        (void)scanf("%td %" XSTR(MAXLEN) "s", &n, buf);
        assert(strlen(buf) == (size_t)n);
        
        printf("%d\n", (is_palindrome(buf, n) ? 1 : 0));
    }
}
