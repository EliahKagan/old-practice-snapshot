#include <cassert>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>
#include <vector>

namespace {
    struct OutEdge {
        int dest;
        int weight;
    };

    using Graph = std::vector<std::vector<OutEdge>>;

    Graph read_graph()
    {
        int vertex_count {};
        std::cin >> vertex_count;
        Graph adj (vertex_count + 1); // add 1 to simulate 1-based indexing

        int edge_count {}, u {}, v {}, weight {};
        for (std::cin >> edge_count; edge_count > 0; --edge_count) {
            std::cin >> u >> v >> weight;
            adj.at(u).push_back({v, weight});
            adj.at(v).push_back({u, weight});
        }

        return adj;
    }

    struct Entry {
        int vertex;
        int cost;
    };

    const auto compare = [](const Entry& lhs, const Entry& rhs) noexcept {
        return lhs.cost != rhs.cost ? lhs.cost < rhs.cost
                                    : lhs.vertex < rhs.vertex;
    };

    constexpr auto infinity = std::numeric_limits<int>::max();

    std::vector<int> dijkstra(const Graph& adj, const int start)
    {
        std::vector<int> costs (adj.size(), infinity);
        costs[start] = 0;

        std::set<Entry, decltype(compare)> entries {compare};
        entries.insert({start, 0});

        while (!entries.empty()) {
            const auto src = [&]() {
                const auto vertex = entries.cbegin()->vertex;
                assert(costs[vertex] == entries.cbegin()->cost);
                entries.erase(entries.cbegin());
                return vertex;
            }();

            for (const auto& edge : adj[src]) {
                const auto dest_cost = costs[src] + edge.weight;
                if (costs[edge.dest] <= dest_cost) continue;

                entries.erase({edge.dest, costs[edge.dest]});
                entries.insert({edge.dest, dest_cost});
                costs[edge.dest] = dest_cost;
            }
        }

        return costs;
    }

    constexpr auto no_path = -1;

    void print_costs(const std::vector<int>& costs, const int start)
    {
        auto sep = "";
        for (auto i = 1; i < costs.size(); ++i) {
            if (i == start) continue;

            std::cout << sep << (costs[i] == infinity ? no_path : costs[i]);
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
        if (!(0 < start && start < adj.size()))
            throw std::out_of_range{"start vertex out of range"};

        print_costs(dijkstra(adj, start), start);
    }
}
