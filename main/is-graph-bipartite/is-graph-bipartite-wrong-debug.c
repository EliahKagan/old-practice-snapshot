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

static inline char asChar(const enum color color)
{
    switch (color) {
    case k_color_white:
        return 'W';

    case k_color_red:
        return 'R';

    case k_color_blue:
        return 'B';
    }

    assert(false);
}

static bool isBipartiteFrom(const int *const *const adj, const int order,
                            const int *const outdegrees, enum color *const vis,
                            const int src, const enum color srcColor)
{
    vis[src] = srcColor;

    printf("src = %d\t", src);
    for (int j = 0; j < order; ++j) printf(" %c", asChar(vis[j]));
    putchar('\n');

    for (int i = 0; i < outdegrees[src]; ++i) {
        const int dest = adj[src][i];

        if (vis[dest] == k_color_white) {
            // The destination has not been visited, so check if the graph is
            // bipartite from there where it is colored with the other color.
            if (!isBipartiteFrom(adj, order, outdegrees, vis, dest,
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

        printf("start = %d\n", start);

        if (isBipartiteFrom(adj, order, outdegrees, vis, start, k_color_red))
            return true;
    }

    return false;
}

bool isBipartite(const int *const *const graph,
                 const int graphRowSize, const int *const graphColSizes)
{
    printf("Row size: %d\n", graphRowSize);

    fputs("Column sizes:", stdout);
    for (int i = 0; i < graphRowSize; ++i) printf(" %d", graphColSizes[i]);
    putchar('\n');

    enum color *vis = xcalloc(graphRowSize, sizeof *vis);

    const bool result = isBipartiteHelper(graph, graphRowSize, graphColSizes,
                                          vis);

    free(vis);
    vis = NULL;

    return result;
}
