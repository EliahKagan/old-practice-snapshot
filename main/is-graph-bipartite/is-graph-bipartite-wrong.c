static void *xcalloc(const size_t count, const size_t size)
{
    void *const ret = calloc(count, size);
    if (!ret) abort();
    return ret;
}

enum color { k_color_white, k_color_red, k_color_blue };

static inline enum color otherColor(const enum color color)
{
    switch (color) {
    case k_color_white:
        abort();

    case k_color_red:
        return k_color_blue;

    case k_color_blue:
        return k_color_red;
    }

    assert(false);
}

static bool isBipartiteFrom(const int *const *const adj,
                            const int *const outdegrees, enum color *const vis,
                            const int src, const enum color srcColor)
{
    vis[src] = srcColor;

    for (int i = 0; i < outdegrees[src]; ++i) {
        const int dest = adj[src][i];

        if (vis[dest] == k_color_white) {
            // The destination has not been visited, so check if the graph is
            // bipartite from there where it is colored with the other color.
            if (!isBipartiteFrom(adj, outdegrees, vis, dest,
                                 otherColor(srcColor)))
                return false;
        }
        else if (vis[dest] == srcColor) {
            // The destination has been visited, so it fails to be bipartite
            // if its coloring is the same as the source vertex's coloring.
            return false;
        }
    }

    return true;
}

static bool isBipartiteHelper(const int *const *const adj, const int order,
                              const int *const outdegrees, enum color *const vis)
{
    for (int start = 0; start < order; ++start) {
        if (vis[start] != k_color_white) continue;

        if (isBipartiteFrom(adj, outdegrees, vis, start, k_color_red))
            return true;
    }

    return false;
}

bool isBipartite(const int *const *const graph,
                 const int graphRowSize, const int *const graphColSizes)
{
    enum color *vis = xcalloc(graphRowSize, sizeof *vis);

    const bool result = isBipartiteHelper(graph, graphRowSize, graphColSizes,
                                          vis);

    free(vis);
    vis = NULL;

    return result;
}
