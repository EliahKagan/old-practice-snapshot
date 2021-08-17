#ifdef NDEBUG
#error Assertions unexpectedly disabled.
#endif

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <queue>
#include <vector>

namespace {
    // An undirected graph, represented as an adjacency list.
    using Graph = std::vector<std::vector<int>>;

    // A visitation state for a vertex, tracking which root the traversal
    // started from (start) and its distance from that root (depth).
    // For a vertex that has not (yet?) been reached, start is zero.
    // This works because we are not also using 0 as a vertex label.
    struct State {
        int start;
        int depth;
    };

    // A visitation list for an undirected graph, tracking roots and distances.
    using Vis = std::vector<State>;

    Graph read_graph(const int vertex_count, int edge_count)
    {
        assert(vertex_count > 0 && edge_count > 0);

        Graph adj (vertex_count + 1);

        while (edge_count-- > 0) {
            int u {}, v {};
            std::cin >> u >> v;
            assert(0 < u && u <= vertex_count && 0 < v && v <= vertex_count);

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        return adj;
    }

    template<typename Action>
    void read_roots_and_do(const int vertex_count, Action action)
    {
        assert(vertex_count >= 0);
        std::vector<int> colors (vertex_count + 1);
        std::copy_n(std::istream_iterator<int>{std::cin},
                    vertex_count, std::next(begin(colors)));

        int root_color {};
        std::cin >> root_color;
        assert(root_color > 0);

        for (auto vertex = 1; vertex <= vertex_count; ++vertex) {
            assert(colors[vertex] > 0);
            if (colors[vertex] == root_color) action(vertex);
        }
    }

    int multi_bfs(const Graph& adj, Vis& vis, std::queue<int>& queue)
    {
        while (!queue.empty()) {
            const auto src = queue.front();
            queue.pop();
            assert(vis[src].start > 0);

            for (const auto& dest : adj[src]) {
                if (vis[dest].start == vis[src].start) continue;

                if (vis[dest].start != 0)
                    return vis[src].depth + vis[dest].depth + 1;

                vis[dest].start = vis[src].start;
                vis[dest].depth = vis[src].depth + 1;
                queue.push(dest);
            }
        }

        return -1;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int vertex_count {}, edge_count {};
    std::cin >> vertex_count >> edge_count;

    const auto adj = read_graph(vertex_count, edge_count);
    Vis vis (vertex_count + 1);
    std::queue<int> queue;

    read_roots_and_do(vertex_count, [&vis, &queue](const int start) {
        vis[start].start = start;
        queue.push(start);
    });

    std::cout << multi_bfs(adj, vis, queue) << '\n';
}
