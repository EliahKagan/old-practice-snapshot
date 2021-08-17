#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

typedef int (*Comparer)(const char *, const char *);

int lexicographic_sort(const char *const a, const char *const b)
{
    return strcmp(a, b);
}

int lexicographic_sort_reverse(const char *const a, const char *const b)
{
    return -strcmp(a, b);
}

int sort_by_length(const char *const a, const char *const b)
{
    const int delta = (int)strlen(a) - (int)strlen(b);
    return delta != 0 ? delta : strcmp(a, b);
}

static int distinct_count(const char *s)
{
    enum { range = CHAR_MAX - CHAR_MIN + 1 };

    bool freqs[range] = {0};
    while (*s) freqs[*s++ - CHAR_MIN] = true;

    int acc = 0;
    for (int i = 0; i < range; ++i) acc += freqs[i];
    return acc;
}

int sort_by_number_of_distinct_characters(const char *const a,
                                          const char *const b)
{
    const int delta = distinct_count(a) - distinct_count(b);
    return delta != 0 ? delta : strcmp(a, b);
}

void string_sort(const char **const arr, const int len,
                 const Comparer cmp)
{
    // Insertion sort is good for small arrays (we have len <= 50).
    for (int right = 1; right < len; ++right) {
        const char *const elem = arr[right];

        int left = right;
        for (; 0 < left && cmp(elem, arr[left - 1]) < 0; --left)
            arr[left] = arr[left - 1];

        arr[left] = elem;
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    char** arr;
	arr = (char**)malloc(n * sizeof(char*));

    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }

    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");
}
