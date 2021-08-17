#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <stack>
#include <string>
#include <vector>

namespace {
    using Graph = std::vector<std::vector<int>>;

    Graph read_graph(const int vertex_count, int edge_count)
    {
        Graph adj (vertex_count);

        while (edge_count-- > 0) {
            int u {}, v {};
            std::cin >> u >> v;

            adj.at(u).push_back(v);
            adj.at(v).push_back(u);
        }

        return adj;
    }

    template<typename F>
    void for_each_component_size(const Graph& adj, F f) noexcept
    {
        std::basic_string<bool> vis (adj.size(), false);
        std::stack<int> stack;

        const auto measure = [&adj, &vis, &stack](const int start) noexcept {
            assert(!vis[start]);
            vis[start] = true;

            assert(stack.empty());
            stack.push(start);

            auto count = 1;

            while (!stack.empty()) {
                const auto src = stack.top();
                stack.pop();

                for (const auto dest : adj[src]) {
                    if (vis[dest]) continue;
                    vis[dest] = true;
                    stack.push(dest);
                    ++count;
                }
            }

            return count;
        };

        for (auto start = 0; start != static_cast<int>(adj.size()); ++start)
            if (!vis[start]) f(measure(start));
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int n {};
    std::cin >> n;
    const auto adj = read_graph(n * 2 + 1, n);

    auto min = std::numeric_limits<int>::max();
    auto max = std::numeric_limits<int>::min();

    for_each_component_size(adj, [&min, &max](const int count) noexcept {
        if (count > 1) {
            min = std::min(min, count);
            max = std::max(max, count);
        }
    });

    std::cout << min << ' ' << max << '\n';
}
