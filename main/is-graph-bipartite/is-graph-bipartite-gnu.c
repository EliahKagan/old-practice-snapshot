static void *xcalloc(const size_t count, const size_t size)
{
    void *const ret = calloc(count, size);
    if (!ret) abort();
    return ret;
}

static bool isBipartiteHelper(const int *const *const adj, const int order,
                              const int *const outdegrees, int *const vis)
{
    __label__ found_odd_cycle;

    void dfs(const int src) {
        assert(vis[src] != 0);

        for (int i = 0; i < outdegrees[src]; ++i) {
            const int dest = adj[src][i];
            if (vis[dest] == -vis[src]) continue;
            if (vis[dest] != 0) goto found_odd_cycle;
            vis[dest] = -vis[src];
            dfs(dest);
        }
    }

    for (int start = 0; start < order; ++start) {
        if (vis[start] != 0) continue;
        vis[start] = 1;
        dfs(start);
    }

    return true;

found_odd_cycle:
    return false;
}

bool isBipartite(const int *const *const graph, const int graphRowSize,
                 const int *const graphColSizes)
{
    int *vis = xcalloc(graphRowSize, sizeof *vis);

    const bool result = isBipartiteHelper(graph, graphRowSize, graphColSizes,
                                          vis);
    free(vis);
    vis = NULL;

    return result;
}
