#include <array>
#include <cstddef>
#include <iostream>
#include <queue>
#include <tuple>

namespace {
    using std::size_t;

    constexpr size_t max_size {20u};

    using Grid = std::array<std::array<bool, max_size>, max_size>;

    Grid get_grid(const size_t n, const size_t m)
    {
        Grid grid {};

        for (std::size_t i {0u}; i != n; ++i) {
            for (std::size_t j {0u}; j != m; ++j) {
                auto e = false;
                std::cin >> e;
                grid.at(i).at(j) = e;
            }
        }

        return grid;
    }

    inline bool can_inhabit(const Grid& grid, const size_t n, const size_t m,
                            const size_t i, const size_t j)
    {
        return i < n && j < m && grid[i][j];
    }

    inline void enqueue_reach(std::queue<std::tuple<size_t, size_t>>& q,
                              const size_t i, const size_t j)
    {
        q.emplace(i, j - 1u);
        q.emplace(i, j + 1u);
        q.emplace(i + 1u, j);
        q.emplace(i - 1u, j);
    }

    int bfs(Grid& grid, const size_t n, const size_t m,  // mutates grid
            size_t i, size_t j, const size_t fi, const size_t fj)
    {
        std::queue<std::tuple<size_t, size_t>> q;
        q.emplace(i, j);

        for (auto distance = 0; !q.empty(); ++distance) {
            for (auto len = q.size(); len != 0u; --len) {
                std::tie(i, j) = q.front();
                q.pop();
                if (!can_inhabit(grid, n, m, i, j)) continue;

                if (i == fi && j == fj) return distance;

                grid[i][j] = false;
                enqueue_reach(q, i, j);
            }
        }

        return -1;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        size_t n {}, m {};
        std::cin >> n >> m;

        auto grid = get_grid(n, m);

        size_t fi {}, fj {};
        std::cin >> fi >> fj;

        std::cout << bfs(grid, n, m, 0u, 0u, fi, fj) << '\n';
    }
}
