// manarag.c - C99 program to determine if two texts are anagrams

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // for strncpy()
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *xmalloc(const size_t size)
{
    void *const p = malloc(size);
    if (p != NULL) return p;
    
    fprintf(stderr, "error: failed to allocate %lu bytes on heap, quitting!\n",
                    (unsigned long)size);
    exit(EXIT_FAILURE);
}

static bool anagram(const char *s, const char *t)
{
    const size_t n = strlen(s);
    if (strlen(t) != n) return false; // texts differ in length
    
    char *u = strncpy((char *)xmalloc(n), t, n);
    
    size_t i = 0;
    for (; i != n; ++i) {
        size_t j = 0;
        for (; j != n; ++j) {
            if (s[i] == u[j]) {
                u[j] = '\0';
                break; // matched
            }
        }
        
        if (j == n) break; // no match
    }
    
    free(u);
    return i == n; // true if each character has a match
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fputs("error: too few arguments\n", stderr);
        return EXIT_FAILURE;
    }
    
    if (argc != 3)
        fputs("warning: too many arguments, some ignored\n", stderr);
    
    const bool anag = anagram(argv[1], argv[2]);
    printf("%s! \"%s\" and \"%s\" %s anagrams.\n", (anag ? "YES" : "NO"),
            argv[1], argv[2], (anag ? "are" : "aren't"));
    
    return EXIT_SUCCESS;
}
