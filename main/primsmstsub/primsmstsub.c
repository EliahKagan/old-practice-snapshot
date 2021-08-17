#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void *xcalloc(const size_t count, const size_t size)
{
    void *const ret = calloc(count, size);
    if (!ret) abort();
    return ret;
}

static void *xrealloc(void *const p, const size_t n)
{
    void *const ret = realloc(p, n);
    if (!ret && n) abort();
    return ret;
}

static void fill(int *const p, const int n, const int value)
{
    for (int i = 0; i < n; ++i) p[i] = value;
}

struct edge {
    int dest;
    int weight;
};

struct vec {
    struct edge *elems;
    int size;
    int capacity;
};

static void vec_free(struct vec *const vp)
{
    free(vp->elems);
    vp->elems = NULL;
    vp->size = vp->capacity = 0;
}

static void vec_detail_expand(struct vec *const vp)
{
    enum { initial_capacity = 1 }; // FIXME: increase after testing

    vp->capacity = (vp->capacity == 0 ? initial_capacity : vp->capacity * 2);
    vp->elems = xrealloc(vp->elems, vp->capacity * sizeof *vp->elems);
}

static inline void vec_emplace_back(struct vec *const vp,
                                    const int dest, const int weight)
{
    if (vp->size == vp->capacity) vec_detail_expand(vp);

    struct edge *const p = vp->elems + vp->size++;
    p->dest = dest;
    p->weight = weight;
}

static inline struct edge *vec_begin(const struct vec *const vp)
{
    return vp->elems;
}

static inline struct edge *vec_end(const struct vec *const vp)
{
    return vp->elems + vp->size;
}

struct graph {
    struct vec *adj;
    int vertex_count;
};

static struct graph graph_read(void)
{
    struct graph g = {0};
    (void)scanf("%d", &g.vertex_count);
    g.adj = xcalloc(++g.vertex_count, sizeof *g.adj); // 1-based indexing

    int edge_count = 0, u = 0, v = 0, weight = 0;
    for ((void)scanf("%d", &edge_count); edge_count > 0; --edge_count) {
        (void)scanf("%d%d%d", &u, &v, &weight);
        vec_emplace_back(&g.adj[u], v, weight);
        vec_emplace_back(&g.adj[v], u, weight);
    }

    return g;
}

static void graph_free(struct graph *const gp)
{
    while (gp->vertex_count > 0) vec_free(&gp->adj[--gp->vertex_count]);

    free(gp->adj);
    gp->adj = NULL;
}

struct entry {
    int vertex;
    int cost;
};

struct heap {
    struct entry *entries;
    int *lookup;
    int size;
};

enum { k_no_index = -1 };

static struct heap heap_init(const int capacity)
{
    struct heap h = {xcalloc(capacity, sizeof *h.entries),
                     xcalloc(capacity, sizeof *h.lookup),
                     0};

    fill(h.lookup, capacity, k_no_index);

    return h;
}

static void heap_free(struct heap *const hp)
{
    free(hp->entries);
    hp->entries = NULL;

    free(hp->lookup);
    hp->lookup = NULL;

    hp->size = -1; // for clarity when debugging
}

static inline bool heap_empty(const struct heap *const hp)
{
    return hp->size == 0;
}

static inline int heap_top_vertex(const struct heap *const hp)
{
    return hp->entries[0].vertex;
}

static inline int heap_top_cost(const struct heap *const hp)
{
    return hp->entries[0].cost;
}

static inline void heap_detail_record(const struct heap *const hp,
                                      const int index)
{
    hp->lookup[hp->entries[index].vertex] = index;
}

static inline int heap_detail_pick_child(const struct heap *const hp,
                                         const int parent)
{
    const int left = parent * 2 + 1;
    if (left >= hp->size) return k_no_index;

    const int right = left + 1;

    if (right == hp->size || hp->entries[left].cost <= hp->entries[right].cost)
        return left;

    return right;
}

static void heap_detail_sift_down(const struct heap *const hp, int parent,
                                  int vertex, int cost)
{
    for (; ; ) {
        const int child = heap_detail_pick_child(hp, parent);
        if (child == k_no_index || cost <= hp->entries[child].cost) break;

        hp->entries[parent].vertex = hp->entries[child].vertex;
        hp->entries[parent].cost = hp->entries[child].cost;
        heap_detail_record(hp, parent);

        parent = child;
    }

    hp->entries[parent].vertex = vertex;
    hp->entries[parent].cost = cost;
    heap_detail_record(hp, parent);
}

static void heap_pop(struct heap *const hp)
{
    hp->lookup[hp->entries[0].vertex] = k_no_index;

    if (--hp->size != 0) {
        heap_detail_sift_down(hp, 0, hp->entries[hp->size].vertex,
                                     hp->entries[hp->size].cost);
    }
}

static void heap_detail_sift_up(const struct heap *const hp, int child,
                                int vertex, int cost)
{
    while (child != 0) {
        const int parent = (child - 1) / 2;
        if (hp->entries[parent].cost <= cost) break;

        hp->entries[child].vertex = hp->entries[parent].vertex;
        hp->entries[child].cost = hp->entries[parent].cost;
        heap_detail_record(hp, child);

        child = parent;
    }

    hp->entries[child].vertex = vertex;
    hp->entries[child].cost = cost;
    heap_detail_record(hp, child);
}

static void heap_emplace_or_decrease(struct heap *const hp,
                                     const int vertex, const int cost)
{
    int index = hp->lookup[vertex];

    if (index == k_no_index)
        index = hp->size++;
    else if (hp->entries[index].cost <= cost)
        return;

    heap_detail_sift_up(hp, index, vertex, cost);
}

static int prim(const struct graph *const gp, const int start)
{
    int total_cost = 0;

    bool *vis = xcalloc(gp->vertex_count, sizeof *vis);
    struct heap h = heap_init(gp->vertex_count);
    heap_emplace_or_decrease(&h, start, 0);

    while (!heap_empty(&h)) {
        const int src = heap_top_vertex(&h), cost = heap_top_cost(&h);
        heap_pop(&h);
        vis[src] = true;
        total_cost += cost;

        const struct vec *rowp = &gp->adj[src];
        for (const struct edge *const ep_end = vec_end(rowp),
                               *ep = vec_begin(rowp); ep != ep_end; ++ep) {
            if (!vis[ep->dest])
                heap_emplace_or_decrease(&h, ep->dest, ep->weight);
        }
    }

    heap_free(&h);
    free(vis);
    vis = NULL;

    return total_cost;
}

int main(void)
{
    struct graph g = graph_read();

    int start = 0;
    (void)scanf("%d", &start);

    printf("%d\n", prim(&g, start));

    graph_free(&g);
}
