// manarag.c - C99 program to determine if two texts are anagrams

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *xmalloc(size_t size);
bool anagram(const char *s, const char *t);
int main(int argc, char *argv[]);

void *xmalloc(size_t size)
{
    void *p = malloc(size);
    if (p != NULL) return p;
    
    fprintf(stderr, "error: failed to allocate %lu bytes on heap, quitting!\n",
                    (unsigned long)size);
    exit(EXIT_FAILURE);
}

bool anagram(const char *s, const char *t)
{
    int n = strlen(s);
    if (strlen(t) != n) return false; // texts differ in length
    
    char *u = strncpy((char *)xmalloc(n), t, n);
    
    int i = 0;
    for (; i != n; ++i) {
        int j = 0;
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
    
    bool anag = anagram(argv[1], argv[2]);
    printf("%s! \"%s\" and \"%s\" are%s anagrams.\n",
           anag ? "YES" : "NO", argv[1], argv[2], anag ? "" : "n't");
    
    return EXIT_SUCCESS;
}
