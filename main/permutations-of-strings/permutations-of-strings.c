#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline bool less_than(char *const *const p, char *const *const q)
{
    return strcmp(*p, *q) < 0;
}

static inline void swap(char **const p, char **const q)
{
    char *const tmp = *p;
    *p = *q;
    *q = tmp;
}

static inline void reverse(char **first, char **last)
{
    while (first < last) swap(first++, --last);
}

static bool do_next_permutation(char **const first, char **const last)
{
    if (last - first < 2) return false;

    char **left = last - 2;
    for (; !less_than(left, left + 1); --left)
        if (left == first) return false;

    char **right = last - 1;
    while (!less_than(left, right)) --right;

    swap(left, right);
    reverse(left + 1, last);
    return true;
}

bool next_permutation(int n, char **s)
{
	/**
	* Complete this method
	* Return 0 when there is no next permutation and 1 otherwise
	* Modify array s to its next permutation
	*/
    return do_next_permutation(s, s + n);
}

int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}
