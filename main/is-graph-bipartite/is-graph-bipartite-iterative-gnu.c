static void *xcalloc(const size_t count, const size_t size)
{
    void *const ret = calloc(count, size);
    if (!ret) abort();
    return ret;
}

static inline void destroy(int **const pp)
{
    free(*pp);
    *pp = NULL;
}

static bool isBipartiteHelper(const int *const *const adj, const int order,
                              const int *const outdegrees, int *const vis,
                              int *const stack)
{
    __label__ found_odd_cycle;

    void dfs(const int start) {
        if (vis[start] != 0) return;
        vis[start] = 1;

        int *top = stack;
        *top++ = start;

        while (top != stack) {
            const int src = *--top;
            assert(vis[src] != 0);

            for (int i = 0; i < outdegrees[src]; ++i) {
                const int dest = adj[src][i];
                if (vis[dest] == -vis[src]) continue;
                if (vis[dest] != 0) goto found_odd_cycle;
                vis[dest] = -vis[src];
                *top++ = dest;
            }
        }
    }

    for (int start = 0; start < order; ++start) dfs(start);
    return true;

found_odd_cycle:
    return false;
}

bool isBipartite(const int *const *const graph, const int graphRowSize,
                 const int *const graphColSizes)
{
    int *vis = xcalloc(graphRowSize, sizeof *vis);
    int *stack = xcalloc(graphRowSize, sizeof *stack);

    const bool result = isBipartiteHelper(graph, graphRowSize, graphColSizes,
                                          vis, stack);
    destroy(&stack);
    destroy(&vis);

    return result;
}
