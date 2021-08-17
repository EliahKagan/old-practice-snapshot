#include <iostream>
#include <queue>
#include <vector>

namespace {
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

    enum class Visitation : char { unvisited, visited };

    int prim(const Graph& adj, const int start)
    {
        auto total_cost = 0;
        std::vector<Visitation> vis (adj.size(), Visitation::unvisited);

        auto heap = get_heap();
        for (heap.push({start, 0}); !heap.empty(); ) {
            const auto src = heap.top().vertex, cost = heap.top().weight;
            heap.pop();
            if (vis[src] != Visitation::unvisited) continue;

            vis[src] = Visitation::visited;
            total_cost += cost;

            for (const auto edge : adj[src]) {
                if (vis[edge.vertex] == Visitation::unvisited)
                    heap.push({edge.vertex, edge.weight});
            }
        }

        return total_cost;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    const auto adj = read_graph();
    int start {};
    std::cin >> start;

    std::cout << prim(adj, start) << '\n';
}
