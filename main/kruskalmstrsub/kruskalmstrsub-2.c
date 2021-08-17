#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static inline void *xcalloc(const size_t count, const size_t size)
{
    void *const ret = calloc(count, size);
    if (!ret) abort();
    return ret;
}

struct dsu {
    int *parents;
    int *ranks;
    int element_count;
};

static struct dsu dsu_make_sets(const int element_count)
{
    struct dsu d = {xcalloc(element_count, sizeof *d.parents),
                    xcalloc(element_count, sizeof *d.ranks),
                    element_count};

    for (int i = 0; i < element_count; ++i) d.parents[i] = i;

    return d;
}

static void dsu_free(struct dsu *const dp)
{
    free(dp->parents);
    dp->parents = NULL;

    free(dp->ranks);
    dp->ranks = NULL;

    dp->element_count = -1; // to make debugging easier
}

static int dsu_detail_find_set(const struct dsu *const dp, int i)
{
    // Find the ancestor.
    int j = i;
    while (j != dp->parents[j]) j = dp->parents[j];

    // Compress the path.
    while (i != j) {
        const int parent = dp->parents[i];
        dp->parents[i] = j;
        i = parent;
    }

    return j;
}

static bool dsu_union(const struct dsu *const dp, int i, int j)
{
    // Find the ancestors and stop if they are already the same.
    i = dsu_detail_find_set(dp, i);
    j = dsu_detail_find_set(dp, j);
    if (i == j) return false;

    // Unite by rank.
    if (dp->ranks[i] < dp->ranks[j]) {
        dp->parents[i] = j;
    } else {
        if (dp->ranks[i] == dp->ranks[j]) ++dp->ranks[i];
        dp->parents[j] = i;
    }

    return true;
}

struct edge {
    int u;
    int v;
    int weight;
};

static inline void edge_read(struct edge *const ep)
{
    (void)scanf("%d%d%d", &ep->u, &ep->v, &ep->weight);
}

static int edge_compare(const void *const p, const void *const q)
{
    const struct edge *const ep = p, *const eq = q;

    if (ep->weight < eq->weight) return -1;
    if (ep->weight > eq->weight) return +1;
    return 0;
}

static struct edge *read_all_edges(const int edge_count)
{
    struct edge *const edges = xcalloc(edge_count, sizeof *edges);
    for (int i = 0; i < edge_count; ++i) edge_read(&edges[i]);
    return edges;
}

static int kruskal(const int vertex_count, const int edge_count,
                   const struct edge *const sorted_edges)
{
    int total_weight = 0;
    struct dsu d = dsu_make_sets(vertex_count + 1); // 1-based indexing

    const struct edge *const ep_end = sorted_edges + edge_count;
    for (const struct edge *ep = sorted_edges; ep != ep_end; ++ep)
        if (dsu_union(&d, ep->u, ep->v)) total_weight += ep->weight;

    dsu_free(&d);
    return total_weight;
}

int main(void)
{
    int vertex_count = 0, edge_count = 0;
    (void)scanf("%d%d", &vertex_count, &edge_count);
    struct edge *edges = read_all_edges(edge_count);

    qsort(edges, edge_count, sizeof *edges, edge_compare);
    const int total_weight = kruskal(vertex_count, edge_count, edges);

    free(edges);
    edges = NULL;

    printf("%d\n", total_weight);
}
