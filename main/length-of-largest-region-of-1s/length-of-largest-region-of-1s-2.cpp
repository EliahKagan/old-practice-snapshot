#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

namespace {
    constexpr std::size_t nmax = 50, mmax = 50;

    using Grid = std::array<std::array<bool, mmax>, nmax>;

    void read_grid(std::size_t& n, std::size_t& m, Grid& grid)
    {
        std::cin >> n >> m;
        assert(0u != n && n <= nmax && 0u != m && m <= mmax);

        for (std::size_t i {0u}; i != n; ++i)
            for (std::size_t j {0u}; j != m; ++j) std::cin >> grid[i][j];
    }

    std::size_t fill_region(Grid& grid,     // returns area of region
                            const std::size_t n, const std::size_t m,
                            const std::size_t i, const std::size_t j)
    {
        static constexpr std::size_t neg (-1);
        if (i == neg || i == n || j == neg || j == m || !grid[i][j]) return 0u;
        grid[i][j] = false;
        
        return 1u + fill_region(grid, n, m, i - 1u, j - 1u)     // northwest
                  + fill_region(grid, n, m, i - 1u, j)          // north
                  + fill_region(grid, n, m, i - 1u, j + 1u)     // northeast
                  + fill_region(grid, n, m, i, j - 1u)          // west
                  + fill_region(grid, n, m, i, j + 1u)          // east
                  + fill_region(grid, n, m, i + 1u, j - 1u)     // southwest
                  + fill_region(grid, n, m, i + 1u, j)          // south
                  + fill_region(grid, n, m, i + 1u, j + 1u);    // southeast
    }

    std::size_t find_max_region(Grid& grid,     // removes (fills) all regions
                                const std::size_t n, const std::size_t m)
    {
        std::size_t a {0u};

        for (std::size_t i {0u}; i != n; ++i) {
            for (std::size_t j {0u}; j != m; ++j)
                if (grid[i][j]) a = std::max(a, fill_region(grid, n, m, i, j));
        }

        return a;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::size_t n {}, m {};
        Grid grid {};
        read_grid(n, m, grid);

        std::cout << find_max_region(grid, n, m) << '\n';
    }
}
