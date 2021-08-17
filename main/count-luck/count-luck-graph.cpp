#include <array>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace {
    using Vertex = std::size_t;

    // An adjaency list representing an undirected graph.
    using Graph = std::vector<std::vector<Vertex>>;

    // A table mapping symbols (besides 'X' and '.') to vertices.
    // Each such special symbol is asssumed to appear at most once.
    using Table = std::map<char, Vertex>;

    enum class Vis : char { unvisited, visited };

    constexpr std::size_t max_degree {4u};

    // Reads a grid of given dimensions.
    // This is a helper function for read_grid_as_graph.
    std::vector<std::string>
    read_grid(const std::size_t height, const std::size_t width)
    {
        std::vector<std::string> grid (height);

        for (auto& row : grid) {
            std::cin >> row;
            if (row.size() != width) std::abort();
        }

        return grid;
    }

    // Enumerates the possible neighbors of a cell.
    // This is a helper function for read_grid_as_graph.
    constexpr std::array<std::tuple<std::size_t, std::size_t>, max_degree>
    neighbors(const std::size_t i, const std::size_t j) noexcept
    {
        return {{{i - 1u, j}, {i + 1u, j}, {i, j + 1u}, {i, j - 1u}}};
    }

    // Returns (graph as adjacency list, special-symbol-to-vertex table).
    std::tuple<Graph, Table> read_grid_as_graph()
    {
        std::size_t height {}, width {};
        std::cin >> height >> width;
        const auto grid = read_grid(height, width);

        const auto vertex = [width](const std::size_t i,
                                    const std::size_t j) noexcept {
            return i * width + j;
        };

        Graph adj (height * width);
        Table tab;

        for (std::size_t i {0u}; i != height; ++i) {
            for (std::size_t j {0u}; j != width; ++j) {
                if (grid[i][j] == 'X') continue;

                if (grid[i][j] != '.')
                  tab.emplace(grid[i][j], vertex(i, j));

                for (const auto& nei : neighbors(i, j)) {
                    std::size_t h {}, k {};
                    std::tie(h, k) = nei;

                    if (h < height && k < width && grid[h][k] != 'X')
                        adj[vertex(i, j)].push_back(vertex(h, k));
                }
            }
        }

        return std::make_tuple(std::move(adj), std::move(tab));
    }

    int count_junctions(const Graph& adj,
                        const Vertex start, const Vertex finish)
    {
        static constexpr auto trapped = -1;
        std::vector<Vis> vis (adj.size(), Vis::unvisited);

        const auto dfs = [&adj, finish, &vis](const auto& me,
                                              const Vertex src) noexcept {
            if (vis[src] == Vis::visited) return trapped;
            vis[src] = Vis::visited;

            if (src == finish) return 0;

            for (const auto dest : adj[src]) {
                const auto junctions = me(me, dest);
                if (junctions != trapped)
                    return (adj[src].size() > 2u ? 1 : 0) + junctions;
            }

            return trapped;
        };

        const auto junctions = dfs(dfs, start);
        if (junctions == trapped) std::abort();
        return (adj[start].size() == 2u ? 1 : 0) + junctions;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t {};
    for (std::cin >> t; t > 0; --t) {
        Graph adj;
        Table tab;
        std::tie(adj, tab) = read_grid_as_graph();

        int guess {};
        std::cin >> guess;

        const auto junctions = count_junctions(adj, tab.at('M'), tab.at('*'));
        std::cerr << junctions << '\n';
        std::cout << (junctions == guess ? "Impressed" : "Oops!") << '\n';
    }
}
