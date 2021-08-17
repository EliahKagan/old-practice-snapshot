#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <tuple>
#include <vector>

namespace {
    using Grid = std::vector<std::string>;

    using Pos = std::tuple<std::size_t, std::size_t>;

    Grid read_grid()
    {
        std::size_t height {}, width {};
        std::cin >> height >> width;
        Grid grid (height);

        for (auto& row : grid) {
            std::cin >> row;
            if (row.size() != width) std::abort();
        }

        return grid;
    }

    Pos find_start(const Grid& grid) noexcept
    {
        for (std::size_t i {0u}; i != grid.size(); ++i) {
            for (std::size_t j {0u}; j != grid[i].size(); ++j)
                if (grid[i][j] == 'M') return std::make_tuple(i, j);
        }

        std::abort(); // Crash "nicely" if there is no start location.
    }

    constexpr std::array<Pos, 4>
    neighbors(const std::size_t i, const std::size_t j) noexcept
    {
        return {{{i - 1u, j}, {i + 1u, j}, {i, j - 1u}, {i, j + 1u}}};
    }

    inline bool can_go(const Grid& grid,
                       const std::size_t i, const std::size_t j) noexcept
    {
        return i < grid.size() && j < grid[i].size() && grid[i][j] != 'X';
    }

    inline int count_choices(const Grid& grid,
                             const std::size_t i, const std::size_t j) noexcept
    {
        auto choices = 0;

        for (const auto& cell : neighbors(i, j)) {
            std::size_t h {}, k {};
            std::tie(h, k) = cell;
            if (can_go(grid, h, k)) ++choices;
        }

        return choices;
    }

    int count_junctions(Grid& grid,
                        const std::size_t i, const std::size_t j) noexcept
    {
        static constexpr auto trapped = -1;
        if (grid[i][j] == '*') return 0;
        grid[i][j] = 'X'; // Won't need to rewrite '.', as the graph is a tree.

        const auto choices = count_choices(grid, i, j);
        if (choices == 0) return trapped; // a simple optimization

        // Try neighbors until we escape or there are no more.
        for (const auto& cell : neighbors(i, j)) {
            std::size_t h {}, k {};
            std::tie(h, k) = cell;
            if (!can_go(grid, h, k)) continue;

            const auto junctions = count_junctions(grid, h, k);
            if (junctions != trapped)
                return (choices == 1 ? 0 : 1) + junctions;
        }

        return trapped;
    }
}

int main()
{
    int t {};
    for (std::cin >> t; t > 0; --t) {
        auto grid = read_grid();

        int guess {};
        std::cin >> guess;

        const auto start = find_start(grid);
        std::size_t i {}, j {};
        std::tie(i, j) = start;

        const auto count = count_junctions(grid, i, j);
        std::cout << (count == guess ? "Impressed" : "Oops!") << '\n';
    }
}
