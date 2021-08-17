#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
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
    int measure(Grid& grid, const std::size_t i, const std::size_t j) noexcept
    {
        if (grid.size() <= i || grid[i].size() <= j || grid[i][j] == 0)
            return 0;
        
        grid[i][j] = 0;
        
        return 1 + measure(grid, i - 1u, j - 1u)  // northwest
                 + measure(grid, i - 1u, j)       // north
                 + measure(grid, i - 1u, j + 1u)  // northeast
                 + measure(grid, i, j - 1u)       // west
                 + measure(grid, i, j + 1u)       // east
                 + measure(grid, i + 1u, j - 1u)  // southwest
                 + measure(grid, i + 1u, j)       // south
                 + measure(grid, i + 1u, j + 1u); // southeast
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
