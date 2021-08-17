#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <queue>
#include <tuple>
#include <vector>

namespace {
    using Grid = std::vector<std::vector<int>>;

    // Reads a grid from standard input.
    Grid read_grid()
    {
        // Make a zeroed-out grid of the appropriate shape.
        std::size_t height {}, width {};
        std::cin >> height >> width;
        Grid grid (height, std::vector<int>(width));

        // Populate the grid.
        for (auto& row : grid)
            for (auto& elem : row) std::cin >> elem;

        return grid;
    }

    // Measures the (i, j) component of the grid. Removes it (mutating grid).
    int measure(Grid& grid, std::size_t i, std::size_t j) noexcept
    {
        auto acc = 0;
        std::queue<std::tuple<std::size_t, std::size_t>> coords;
        coords.emplace(i, j);

        while (!coords.empty()) {
            std::tie(i, j) = coords.front();
            coords.pop();

            if (grid.size() <= i || grid[i].size() <= j || grid[i][j] == 0)
                continue;

            grid[i][j] = 0;
            ++acc;

            coords.emplace(i - 1u, j - 1u); // northwest
            coords.emplace(i - 1u, j);      // north
            coords.emplace(i - 1u, j + 1u); // northeast
            coords.emplace(i, j - 1u);      // west
            coords.emplace(i, j + 1u);      // east
            coords.emplace(i + 1u, j - 1u); // southwest
            coords.emplace(i + 1u, j);      // south
            coords.emplace(i + 1u, j + 1u); // southeast
        }

        return acc;
    }

    // Finds the maximum components size destructively (mutating grid).
    int max_component_size(Grid&& grid) noexcept
    {
        auto acc = 0;

        for (std::size_t i {0u}; i != grid.size(); ++i) {
            for (std::size_t j {0u}; j != grid[i].size(); ++j)
                acc = std::max(acc, measure(grid, i, j));
        }

        return acc;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cout << max_component_size(read_grid()) << '\n';
}
