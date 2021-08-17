#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

namespace {
    using std::size_t;

    using Adjacents = std::vector<std::vector<size_t>>;

    struct Edge {
        size_t first, second, weight;
    };

    std::vector<Edge> read_edges(const size_t edge_count)
    {
        std::vector<Edge> edges (edge_count);

        for (auto& edge : edges)
            std::cin >> edge.first >> edge.second >> edge.weight;

        return edges;
    }

    Adjacents compute_adjacents(const size_t vertex_count,
                                const std::vector<Edge>& edges)
    {
        Adjacents adj (vertex_count);

        for (const auto& edge : edges) {
            adj.at(edge.first).push_back(edge.second);
            adj.at(edge.second).push_back(edge.first);
        }

        return adj;
    }

    bool dfs(const Adjacents& adj, std::vector<bool>& vis,
             const size_t src, const size_t dest) noexcept
    {
        if (src == dest) return true;
        vis[src] = true;

        for (const auto next : adj[src])
            if (!vis[next] && dfs(adj, vis, next, dest)) return true;

        return false;
    }

    bool edge_is_redundant(const Adjacents& adj, const size_t first,
                                                 const size_t second)
    {
        if (first == second) return false;

        std::vector<bool> vis (adj.size());
        vis[first] = true;

        for (const auto src : adj[first])
            if (src != second && dfs(adj, vis, src, second)) return true;

        return false;
    }

    void remove_neighbor(std::vector<size_t>& row, const size_t neighbor)
    {
        const auto p = std::find(std::begin(row), std::end(row), neighbor);
        assert(p != std::end(row));
        std::swap(*p, row.back());
        row.pop_back();
    }

    void remove_edge(Adjacents& adj, const size_t first, const size_t second)
    {
        remove_neighbor(adj[first], second);
        remove_neighbor(adj[second], first);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        size_t v {}, e {};
        std::cin >> v >> e;

        auto edges = read_edges(e);
        auto adj = compute_adjacents(v + 1u, edges);

        std::sort(std::begin(edges), std::end(edges), [](const Edge& lhs,
                                                         const Edge& rhs) {
            // Sort edges in reverse order (i.e., nonincreasingly) by weight.
            return lhs.weight > rhs.weight;
        });

        size_t sum {0u};
        for (const auto& edge : edges) {
            if (edge_is_redundant(adj, edge.first, edge.second))
                remove_edge(adj, edge.first, edge.second);
            else sum += edge.weight;
        }

        std::cout << sum << '\n';
    }
}
