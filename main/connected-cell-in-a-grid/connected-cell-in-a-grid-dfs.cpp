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
    constexpr std::size_t nmax = 10, mmax = 10;

    using Grid = std::array<std::array<bool, mmax>, nmax>;

    void read_grid(std::size_t& n, std::size_t& m, Grid& grid)
    {
        std::cin >> n >> m;
        assert(0u != n && n <= nmax && 0u != m && m <= mmax);

        for (std::size_t i {0u}; i != n; ++i)
            for (std::size_t j {0u}; j != m; ++j) std::cin >> grid[i][j];
    }

    std::size_t fill_and_measure_region(Grid& grid, const std::size_t imax,
            const std::size_t jmax, const std::size_t i, const std::size_t j)
    {
        if (!grid[i][j]) return 0u;
        grid[i][j] = false;
        
        std::size_t a {1u};

        if (i != 0u) {
            if (j != 0u)
                a += fill_and_measure_region(grid, imax, jmax, i - 1u, j - 1u);
            
            a += fill_and_measure_region(grid, imax, jmax, i - 1u, j);
            
            if (j != jmax)
                a += fill_and_measure_region(grid, imax, jmax, i - 1u, j + 1u);
        }

        if (j != 0u)
            a += fill_and_measure_region(grid, imax, jmax, i, j - 1u);
        
        if (j != jmax)
            a += fill_and_measure_region(grid, imax, jmax, i, j + 1u);

        if (i != imax) {
            if (j != 0u)
                a += fill_and_measure_region(grid, imax, jmax, i + 1u, j - 1u);
            
            a += fill_and_measure_region(grid, imax, jmax, i + 1u, j);
            
            if (j != jmax)
                a += fill_and_measure_region(grid, imax, jmax, i + 1u, j + 1u);
        }
        
        return a;
    }

    std::size_t find_max_region( // removes (fills) all regions
            Grid& grid, const std::size_t n, const std::size_t m)
    {
        std::size_t a {0u};

        for (std::size_t i {0u}; i != n; ++i) {
            for (std::size_t j {0u}; j != m; ++j) {
                if (grid[i][j]) {
                    a = std::max(a, fill_and_measure_region(grid, n - 1u,
                                                            m - 1u, i, j));
                }
            }
        }

        return a;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    std::size_t n {}, m {};
    Grid grid {};
    read_grid(n, m, grid);

    std::cout << find_max_region(grid, n, m) << '\n';
}
