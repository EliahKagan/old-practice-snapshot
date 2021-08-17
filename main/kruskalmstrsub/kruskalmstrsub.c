#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#define restrict __restrict
#endif

static void *xmalloc(const size_t size)
{
    void *const p = malloc(size);
    if (p == NULL) abort();
    return p;
}

// Creates count separate sets, all of one element.
static int *make_sets(const int count)
{
    int *const a = xmalloc(sizeof *a * (size_t)count);
    for (int i = 0; i != count; ++i) a[i] = -1;
    return a;
}

// Returns the representative element of the set that contains i.
static int find_set(int *const a, int i)
{
    // find the ancestor
    int j = i;
    while (a[j] >= 0) j = a[j];

    // compress the path
    while (i != j) {
        const int parent = a[i];
        a[i] = j;
        i = parent;
    }

    return j;
}

// If i and j are in different sets, joins them and returns true.
// If they were already in the same set, returns false.
static bool unite(int *const a, int i, int j)
{
    // find the ancestors and check if the sets are the same
    i = find_set(a, i);
    j = find_set(a, j);
    if (i == j) return false;

    // union by rank
    if (a[i] > a[j]) {
        a[i] = j; // j has superior (more negative) rank
    } else {
        if (a[i] == a[j]) --a[i]; // i and j are of equal rank, so promote i
        a[j] = i;
    }

    return true;
}

struct edge {
    int x, y, r;
};

static inline void read_edge(struct edge *const e)
{
    if (scanf(" %d %d %d", &e->x, &e->y, &e->r) != 3) abort();
}

static struct edge *read_edges(const int edge_count)
{
    struct edge *const edges = xmalloc(sizeof *edges * (size_t)edge_count);
    for (int i = 0; i != edge_count; ++i) read_edge(&edges[i]);
    return edges;
}

static int compare_edges(const void *const lhsp, const void *const rhsp)
{
    // Quickly compare edges by weight. This only works for edge weights of
    // small magnitudes. DO NOT use this if the difference between any two
    // weights might be less than INT_MIN or greater than INT_MAX. However, it
    // is fine to ignore other "requirements" as to how edges are selected for
    // an MST when the only property of the MST that is reported is its total
    // weight, because all MSTs of a graph have the same weight as one another.
    return ((const struct edge*)lhsp)->r - ((const struct edge*)rhsp)->r;
}

int main(void)
{
    int n = 0, m = 0;
    if (scanf("%d %d", &n, &m) != 2) abort();
    struct edge *restrict const edges = read_edges(m);

    qsort(edges, (size_t)m, sizeof *edges, compare_edges);
    int *restrict const a = make_sets(n + 1); // because we're not using 0

    int acc = 0;
    for (int i = 0; i != m; ++i)
        if (unite(a, edges[i].x, edges[i].y)) acc += edges[i].r;

    printf("%d\n", acc);

    free(a);
    free(edges);
}
