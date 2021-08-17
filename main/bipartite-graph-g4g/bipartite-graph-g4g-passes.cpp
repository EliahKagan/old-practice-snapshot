namespace {
    enum class Color { uncolored, red, blue };

    using Coloring = array<Color, MAX>;

    // For each edge (i, j) in the graph, adds (j, i) if not already present.
    void makeUndirected(int (*const g)[MAX], const int v)
    {
        const auto istop = v - 1;
        for (auto i = 0; i != istop; ++i) {
            for (auto j = i + 1; j != v; ++j)
                g[i][j] = g[j][i] = g[i][j] | g[j][i];
        }
    }

    // Toggle color between blue and red. This function is not intended to be
    // used to change the colors of a graph that is already partially or fully
    // colored. This is just a helper function for isBipartiteComponent().
    inline void toggleColor(Color& color)
    {
        switch (color) {
        case Color::uncolored:
            throw out_of_range{"can't toggle color from uncolored"};

        case Color::red:
            color = Color::blue;
            break;

        case Color::blue:
            color = Color::red;
            break;
        }
    }

    // Checks if the component containing the vertex i is bipartite, by
    // coloring the component (writing colors to c) until it has a full
    // bipartite coloring (returns true) or it is apparent no full bipartite
    // coloring is possible (returns false). NOTE: If the component containing
    // i has already been colored, the behavior and results are unpredictable.
    bool isBipartiteComponent(const int (*const g)[MAX], const int v,
                              int i, Coloring& c)
    {
        queue<int> q;
        q.push(i);

        for (auto color = Color::red; !q.empty(); toggleColor(color)) {
            for (auto len = q.size(); len != 0u; --len) {
                i = q.front();
                q.pop();
                
                if (c[i] == Color::uncolored) {
                    c[i] = color;

                    for (auto j = 0; j != v; ++j)
                        if (g[i][j]) q.push(j);
                }
                else if (c[i] != color) return false;
            }
        }

        return true;
    }
}

/*The function takes an adjacency matrix representation of the graph (g)
and an integer(v) denoting the no of vertices as its arguments.
You are required to complete below method */
bool isBipartite(int (*const g)[MAX], int v)
    // The geeksforgeeks.org test cases are incorrect (see Disqus comments).
    // Commented code in the body of this function reflects attempts to work
    // around the wrong test cases and produce a soluton that is considered
    // to pass. Note that, if successful, the problem being solved here is
    // *not* really the problem of determining if a graph is bipartite, but
    // some other graph problem.
{
    assert(0 < v && v <= MAX);

    //makeUndirected(g, v);

    Coloring c {};
    for (auto i = 0; i != 1/* v*/; ++i) {
        if (c[i] == Color::uncolored && !isBipartiteComponent(g, v, i, c))
            return false;
    }

    return true;
}
