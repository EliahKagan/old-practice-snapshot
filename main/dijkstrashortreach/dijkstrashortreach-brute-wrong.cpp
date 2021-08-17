#ifdef NDEBUG
#error Assertions unexpectedly disabled.
#endif

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

namespace {
    struct OutEdge {
        int dest;
        int weight;
    };

    using Graph = std::vector<std::vector<OutEdge>>;

    Graph read_graph()
    {
        auto vertex_count = 0, edge_count = 0;
        std::cin >> vertex_count >> edge_count;
        assert(vertex_count > 0 && edge_count > 0);
        Graph adj (vertex_count + 1); // +1 for 1-based indexing

        while (edge_count--) {
            auto u = 0, v = 0, weight = -1;
            std::cin >> u >> v >> weight;
            assert(0 < u && u <= vertex_count && 0 < v && v <= vertex_count);
            assert(0 <= weight);

            adj[u].push_back({v, weight});
            adj[v].push_back({u, weight});
        }

        return adj;
    }

    constexpr auto infinity = std::numeric_limits<int>::max();
    constexpr auto unreachable = -1;

    std::vector<int> dijkstra(const Graph& adj, int start)
    {
        const auto order = static_cast<int>(adj.size());
        std::vector<int> costs (order, infinity);
        auto start_cost = costs[start] = 0;

        do {
            costs[start] = ~start_cost;

            for (const auto edge : adj[start]) {
                costs[edge.dest] = std::min(costs[edge.dest],
                                            start_cost + edge.weight);
            }

            for (auto next = 0; next != order; ++next) {
                const auto next_cost = costs[next];
                if (0 <= next_cost && next_cost <= start_cost) {
                    start_cost = next_cost;
                    start = next;
                }
            }

            start_cost = costs[start];
        }
        while (0 <= start_cost);

        for (auto& cost : costs) cost = (cost < 0 ? ~cost : unreachable);
        return costs;
    }

    void print_costs(const std::vector<int>& costs, const int start)
    {
        for (auto vertex = 1; vertex < start; ++vertex)
            std::cout << costs[vertex] << ' ';

        const auto order = static_cast<int>(costs.size());
        for (auto vertex = start + 1; vertex < order; ++vertex)
            std::cout << costs[vertex] << ' ';

        std::cout << '\n';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t {};
    for (std::cin >> t; t > 0; --t) {
        auto adj = read_graph();

        auto start = 0;
        std::cin >> start;
        assert(0 < start && start < adj.size());

        print_costs(dijkstra(adj, start), start);
    }
}
