static inline void *xcalloc(const size_t count, const size_t size)
{
    void *const ret = calloc(count, size);
    if (!ret) abort();
    return ret;
}

static inline void *xrealloc(void *const p, const size_t n)
{
    void *const ret = realloc(p, n);
    if (!ret && n) abort();
    return ret;
}

struct vec {
    int *elems;
    int length;
    int capacity;
};

static void vec_free(struct vec *const vp)
{
    free(vp->elems);
    vp->elems = NULL;

    vp->length = vp->capacity = 0;
}

static void vec_detail_expand(struct vec *const vp)
{
    enum { k_initial_capacity = 1 };

    vp->capacity = (vp->capacity == 0 ? k_initial_capacity : vp->capacity * 2);
    vp->elems = xrealloc(vp->elems, vp->capacity * sizeof *vp->elems);
}

static inline void vec_push_back(struct vec *const vp, const int x)
{
    if (vp->length == vp->capacity) vec_detail_expand(vp);
    vp->elems[vp->length++] = x;
}

static inline int *vec_begin(const struct vec *const vp)
{
    return vp->elems;
}

static inline int *vec_end(const struct vec *const vp)
{
    return vp->elems + vp->length;
}

struct graph {
    struct vec *adj;
    int vertex_count;
};

static struct graph graph_init(const int vertex_count)
{
    return (struct graph){xcalloc(vertex_count, sizeof(struct vec)),
                          vertex_count};
}

static void graph_free(struct graph *const gp)
{
    while (gp->vertex_count > 0) vec_free(&gp->adj[--gp->vertex_count]);

    free(gp->adj);
    gp->adj = NULL;
}

static inline void graph_add_edge(const struct graph *const gp,
                                  const int src, const int dest)
{
    vec_push_back(&gp->adj[src], dest);
}

// Visitation states for depth-first traversal of a directed graph.
enum color {
    k_color_white,  // unvisited (this enumerator must appear first)
    k_color_gray,   // visited but not yet fully explored
    k_color_black   // visited and fully explored
};

struct graph_detail_dfs {
    const struct graph *const gp;
    enum color *vis;
    int *out;
};

static struct graph_detail_dfs
graph_detail_dfs_init(const struct graph *const gp, int *const out)
{
    return (struct graph_detail_dfs){
            gp, xcalloc(gp->vertex_count, sizeof(enum color)), out};
}

static void graph_detail_dfs_free(struct graph_detail_dfs *const dp)
{
    free(dp->vis);
    dp->vis = NULL;

    dp->out = NULL;
}

static bool graph_detail_has_cycle(struct graph_detail_dfs *const dp,
                                   const int src);

static bool graph_detail_has_cycle_recurse(struct graph_detail_dfs *const dp,
                                           const int src)
{
    const struct vec *const rowp = &dp->gp->adj[src];

    const int *const destp_end = vec_end(rowp);
    for (const int *destp = vec_begin(rowp); destp != destp_end; ++destp)
        if (graph_detail_has_cycle(dp, *destp)) return true;

    return false;
}

static bool graph_detail_has_cycle(struct graph_detail_dfs *const dp,
                                   const int src)
{
    switch (dp->vis[src]) {
    case k_color_white:
        dp->vis[src] = k_color_gray;
        if (graph_detail_has_cycle_recurse(dp, src)) return true;
        dp->vis[src] = k_color_black;

        *dp->out++ = src;
        return false;

    case k_color_gray:
        return true;

    case k_color_black:
        return false;
    }

    abort(); // unreachable unless an invalid vistation state is encountered
}

static int *graph_reverse_topological_sort(const struct graph *const gp)
{
    int *ret = xcalloc(gp->vertex_count, sizeof *ret);
    struct graph_detail_dfs d = graph_detail_dfs_init(gp, ret);

    int start = 0;
    while (start < gp->vertex_count && !graph_detail_has_cycle(&d, start))
        ++start;

    assert(start == d.out - ret);

    if (start < gp->vertex_count) {
        free(ret);
        ret = NULL;
    }

    graph_detail_dfs_free(&d);
    return ret;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findOrder(const int numCourses, int **const prerequisites,
               const int prerequisitesRowSize, int *const prerequisitesColSizes,
               int *const returnSize)
{
    const int vertex_count = numCourses; // courses are 0, ..., vertex_count - 1
    const int edge_count = prerequisitesRowSize; // the number of prerequisites
    (void)prerequisitesColSizes; // an edge_count-length sequence of all 2s

    struct graph g = graph_init(vertex_count);

    for (int i = 0; i < edge_count; ++i)
        graph_add_edge(&g, prerequisites[i][0], prerequisites[i][1]);

    int *const ret = graph_reverse_topological_sort(&g);

    graph_free(&g);

    *returnSize = (ret ? vertex_count : 0);
    return ret;
}
