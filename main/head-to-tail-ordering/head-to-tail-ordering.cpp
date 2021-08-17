#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
    using Graph = std::array<std::array<int, 26u>, 26u>; // adjacency matrix

    int read_graph(Graph& graph) // returns the total number of edges
    {
        auto n = 0;
        std::cin >> n;

        for (auto i = n; i != 0; --i) {
            std::string s;
            std::cin >> s;
            
            if (s.empty())
                throw std::out_of_range{"empty string has no front or back"};

            ++graph.at(static_cast<std::size_t>(s.front() - 'a'))
                   .at(static_cast<std::size_t>(s.back() - 'a'));
        }

        return n;
    }

    // Traverses graph (depth first) from vertex i, each edge at most once.
    // Returns the maximum number of edges that can be visited this way.
    int dfs(Graph& graph, const std::size_t i)
    {
        auto n = 0;

        for (std::size_t j {0u}; j != graph.size(); ++j) {
            if (graph[i][j] != 0) {
                --graph[i][j];
                n = std::max(n, 1 + dfs(graph, j));
                ++graph[i][j]; //-V127 sum of matrix is within bounds
            }
        }

        return n;
    }

    // Traverses graph (depth first) from each possible starting vertex,
    // visiting each edge at most once. Returns the maximum number of edges
    // that can be visited this way.
    int dfs(Graph& graph)
    {
        auto n = 0;

        for (std::size_t i {0u}; i != graph.size(); ++i)
            n = std::max(n, dfs(graph, i));

        return n;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        Graph graph {};
        const auto n = read_graph(graph);

        std::cout << (dfs(graph) == n
                        ? "Head to tail ordering is possible.\n"
                        : "Head to tail ordering is not possible.\n");
    }
}
