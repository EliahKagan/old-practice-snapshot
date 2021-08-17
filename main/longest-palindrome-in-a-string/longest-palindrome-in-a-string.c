#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XSTR(a) STR(a)
#define STR(a) #a

#define MAXLEN 1024

struct string_view { // Specifies the window [first, first + length).
    const char *first;
    const ptrdiff_t length;
};

// Checks if [first, last) is a palindrome.
static inline bool is_palindrome(const char *first, const char *last)
{
    while (first < last)
        if (*first++ != *--last) return false;

    return true;
}

// Checks if the window [first, mid), or any window that may be obtained by
// sliding it to the right such that its width stays the same and mid <= right,
// is a palindrome. Returns the left endpoint of the first matching window,
// or NULL if there is no match.
static inline const char *slide_window_to_palindrome(
        const char *first, const char *mid, const char *const last)
{
    for (; ; ++first, ++mid) {
        if (is_palindrome(first, mid)) return first;
        if (mid == last) return NULL;
    }
}

// Finds the first maximum-length palindrome in [first, last).
static struct string_view find_longest_palindrome(const char *const first,
                                                  const char *const last)
{
    for (const char *mid = last; mid != first; --mid) {
        const char *const match = slide_window_to_palindrome(first, mid, last);
        if (match != NULL) return (struct string_view) { match, mid - first };
    }
    
    assert(first == last); // nonempty worst case was a 1-character palindrome
    return (struct string_view) { first, 0 };
}

// Prints the characters in the window denoted by the view, then a newline.
static inline void print(const struct string_view view)
{
    printf("%.*s\n", (int)view.length, view.first);
}

int main(void)
{
    char buf[MAXLEN + 1] = { 0 };
    
    int t = 0;
    for ((void)scanf("%d", &t); t > 0; --t) {
        if (scanf("%" XSTR(MAXLEN) "s", buf) != 1) abort();
        print(find_longest_palindrome(buf, strchr(buf, '\0')));
    }
}
