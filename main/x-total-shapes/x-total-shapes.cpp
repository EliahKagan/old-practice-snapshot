#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace {
    std::vector<std::string> read_grid()
    {
        std::vector<std::string>::size_type n {};
        std::string::size_type m {};
        std::cin >> n >> m;
        assert(n != 0u && m != 0u);

        std::vector<std::string> grid (n);
        for (auto& row : grid) {
            std::cin >> row;
            assert(row.size() == m);
        }

        return grid;
    }

    void fill_grid(std::vector<std::string>& grid,
                   const std::vector<std::string>::size_type i,
                   const std::string::size_type j)
    {
        if (grid[i][j] == 'X') {
            grid[i][j] = 'O';

            if (i != 0u)                    fill_grid(grid, i - 1u, j);
            if (i != grid.size() - 1u)      fill_grid(grid, i + 1u, j);
            if (j != 0u)                    fill_grid(grid, i, j - 1u);
            if (j != grid[0].size() - 1u)   fill_grid(grid, i, j + 1u);
        }
    }

    std::size_t fill_and_count_regions(std::vector<std::string>& grid)
    {
        std::size_t count {0u};

        for (decltype(grid.size()) i {0u}; i != grid.size(); ++i) {
            for (decltype(grid[i].size()) j {0u}; j != grid[i].size(); ++j) {
                if (grid[i][j] == 'X') {
                    fill_grid(grid, i, j);
                    ++count;
                }
            }
        }

        return count;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto grid = read_grid();
        std::cout << fill_and_count_regions(grid) << '\n';
    }
}
