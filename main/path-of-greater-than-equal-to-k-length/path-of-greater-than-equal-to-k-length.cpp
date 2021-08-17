#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

namespace {
    using Graph = std::vector<std::vector<std::pair<std::size_t, int>>>;

    Graph read_graph(const std::size_t v, int e)
    {
        Graph graph (v);

        while (e-- > 0) { // read source, destination, and weight ("distance")
            std::size_t a {}, b {};
            int w {};
            std::cin >> a >> b >> w;

            graph.at(a).emplace_back(b, w);
            graph.at(b).emplace_back(a, w);
        }

        return graph;
    }

    bool dfs(const Graph& graph, const int k, const std::size_t cur,
             std::vector<bool>& visited)
    {
        if (k <= 0) return true;
        visited[cur] = true;

        for (const auto& ent : graph[cur]) { // ent = (neighbor, weight)
            if (!visited[ent.first]
                    && dfs(graph, k - ent.second, ent.first, visited))
                return true;
        }

        visited[cur] = false;
        return false;
    }

    bool dfs(const Graph& graph, const int k)
    {
        std::vector<bool> visited (graph.size());
        return dfs(graph, k, 0u, visited);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t {};
    for (std::cin >> t; t > 0; --t) {
        std::size_t v {};
        int e {}, k {};
        std::cin >> v >> e >> k;

        std::cout << dfs(read_graph(v, e), k) << '\n';
    }
}
