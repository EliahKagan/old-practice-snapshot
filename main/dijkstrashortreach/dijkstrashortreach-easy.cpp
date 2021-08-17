#include <iostream>
#include <queue>
#include <vector>

namespace {
    constexpr auto no_path = -1;

    struct Edge {
        int vertex;
        int weight;
    };

    using Graph = std::vector<std::vector<Edge>>;

    Graph read_graph()
    {
        int vertex_count {};
        std::cin >> vertex_count;
        Graph adj (vertex_count + 1); // add 1 for 1-based indexing

        int edge_count {}, u {}, v {}, weight {};
        for (std::cin >> edge_count; edge_count > 0; --edge_count) {
            std::cin >> u >> v >> weight;
            adj[u].push_back({v, weight});
            adj[v].push_back({u, weight});
        }

        return adj;
    }

    auto get_heap() noexcept
    {
        const auto compare = [](const Edge& lhs, const Edge& rhs) noexcept {
            return lhs.weight > rhs.weight;
        };

        return std::priority_queue<
                Edge, std::vector<Edge>, decltype(compare)>{compare};
    }

    std::vector<int> dijkstra(const Graph& adj, const int start)
    {
        std::vector<int> costs (adj.size(), no_path);

        auto heap = get_heap();
        for (heap.push({start, 0}); !heap.empty(); ) {
            const auto src = heap.top().vertex, cost = heap.top().weight;
            heap.pop();
            if (costs[src] != no_path) continue;

            costs[src] = cost;
            for (const auto edge : adj[src]) {
                const auto dest = edge.vertex, weight = edge.weight;
                if (costs[dest] == no_path) heap.push({dest, cost + weight});
            }
        }

        return costs;
    }

    void print_costs(const std::vector<int>& costs, const int start)
    {
        auto sep = "";

        const auto len = static_cast<int>(costs.size());
        for (auto i = 1; i < len; ++i) {
            if (i == start) continue;

            std::cout << sep << costs[i];
            sep = " ";
        }

        std::cout << '\n';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t {};
    for (std::cin >> t; t > 0; --t) {
        const auto adj = read_graph();
        int start {};
        std::cin >> start;

        const auto costs = dijkstra(adj, start);
        print_costs(costs, start);
    }
}
