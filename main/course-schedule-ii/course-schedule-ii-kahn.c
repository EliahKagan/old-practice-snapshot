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
    int *inorders;
    int vertex_count;
    bool used;
};

static struct graph graph_init(const int vertex_count)
{
    return (struct graph){xcalloc(vertex_count, sizeof(struct vec)),
                          xcalloc(vertex_count, sizeof(int)),
                          vertex_count,
                          false};
}

static void graph_free(struct graph *const gp)
{
    while (gp->vertex_count > 0) vec_free(&gp->adj[--gp->vertex_count]);

    free(gp->adj);
    gp->adj = NULL;

    free(gp->inorders);
    gp->inorders = NULL;

    // gp->used is deliberately left alone, for debugging purposes.
}

static inline void graph_add_edge(const struct graph *const gp,
                                  const int src, const int dest)
{
    vec_push_back(&gp->adj[src], dest);
    ++gp->inorders[dest];
}

static int *graph_detail_get_roots(const struct graph *const gp, int *outp)
{
    for (int dest = 0; dest < gp->vertex_count; ++dest)
        if (gp->inorders[dest] == 0) *outp++ = dest;

    return outp;
}

static int *graph_topological_sort(struct graph *const gp)
{
    if (gp->used) abort(); // gp->inorders would no longer be correct.
    gp->used = true;

    int *ret = xcalloc(gp->vertex_count, sizeof *ret);
    int *right = graph_detail_get_roots(gp, ret);

    for (int *left = ret; left != right; ++left) {
        const struct vec *const rowp = &gp->adj[*left];

        const int *const destp_end = vec_end(rowp);
        for (const int *destp = vec_begin(rowp); destp != destp_end; ++destp)
            if (--gp->inorders[*destp] == 0) *right++ = *destp;
    }

    if (right - ret != gp->vertex_count) { // The graph has a cycle.
        free(ret);
        ret = NULL;
    }

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
        graph_add_edge(&g, prerequisites[i][1], prerequisites[i][0]);

    int *const ret = graph_topological_sort(&g);

    graph_free(&g);

    *returnSize = (ret ? vertex_count : 0);
    return ret;
}
