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

static int *graph_detail_reverse_topological_sort(const struct graph *const gp,
                                                  enum color *const vis)
{
    __label__ found_cycle;
    int *ret = xcalloc(gp->vertex_count, sizeof *ret), *out = ret;

    void dfs(const int src) {
        switch (vis[src]) {
        case k_color_white:
            vis[src] = k_color_gray;
            {
                const struct vec *const rowp = &gp->adj[src];

                const int *const destp_end = vec_end(rowp);
                for (const int *destp = vec_begin(rowp); destp != destp_end;
                                                         ++destp)
                    dfs(*destp);
            }
            vis[src] = k_color_black;

            *out++ = src;
            return;

        case k_color_gray:
            goto found_cycle;

        case k_color_black:
            return;
        }

        abort(); // only reached if a vistation state has an invalid value
    }

    for (int start = 0; start < gp->vertex_count; ++start) dfs(start);
    assert(out - ret == gp->vertex_count);
    return ret;

found_cycle:
    free(ret);
    return NULL;
}

static int *graph_reverse_topological_sort(const struct graph *const gp)
{
    enum color *vis = xcalloc(gp->vertex_count, sizeof *vis);
    int *const ret = graph_detail_reverse_topological_sort(gp, vis);
    free(vis);
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
