#include <cstddef>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace {
    using Graph = std::vector<std::vector<std::size_t>>; // adjacency lists

    inline void check_src_dest(const Graph& graph, const std::size_t src,
                                                   const std::size_t dest)
    {
        if (src >= graph.size() || dest >= graph.size())
            throw std::out_of_range{"no such vertex"};
    }

    inline void add_edge(Graph& graph, const std::size_t src,
                                       const std::size_t dest)
    {
        check_src_dest(graph, src, dest);
        graph[src].push_back(dest);
    }

    Graph read_graph()
    {
        std::size_t v {}, e {};
        std::cin >> v >> e;

        Graph graph (v);

        while (e-- != 0u) {
            std::size_t src {}, dest {};
            std::cin >> src >> dest;
            add_edge(graph, src, dest);
        }

        return graph;
    }

    int count_paths(const Graph& graph, const std::size_t src,
                                        const std::size_t dest)
    {
        std::vector<bool> vis (graph.size());

        const std::function<int(std::size_t)>
        dfs {[&dfs, &graph, &vis, dest](const std::size_t cur) {
            if (vis[cur]) return 0;
            if (cur == dest) return 1;

            vis[cur] = true;

            auto ret = 0;
            for (const auto next : graph[cur]) ret += dfs(next);

            vis[cur] = false;
            return ret;
        }};

        return dfs(src);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto graph = read_graph();

        std::size_t src {}, dest {};
        std::cin >> src >> dest;
        check_src_dest(graph, src, dest);

        std::cout << count_paths(graph, src, dest) << '\n';
    }
}
