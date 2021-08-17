    Graph build_graph(const size_t m, const size_t n,
                      const std::vector<size_t>& grid)
    {
        assert(grid.size() == m * n);

        auto graph = build_generic_graph(m, n);

        for (auto& row : graph) {
            std::sort(std::begin(row), std::end(row), [](const size_t x,
                                                         const size_t y) {
                // By sorting each row of the adjacency list in alphabetical
                // order of indexed letter, graph traversal will match words
                // in lexicographic order. [FIXME: No it won't! Scrap this.]
                return row[x] < row[y];
            });
        }

        return graph;
    }
