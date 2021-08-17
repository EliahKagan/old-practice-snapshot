#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

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

    void fill_region(Grid& grid, const std::size_t imax,
            const std::size_t jmax, const std::size_t i, const std::size_t j)
    {
        if (!grid[i][j]) return;
        grid[i][j] = false;

        if (i != 0u) {
            if (j != 0u) fill_region(grid, imax, jmax, i - 1u, j - 1u);
            fill_region(grid, imax, jmax, i - 1u, j);
            if (j != jmax) fill_region(grid, imax, jmax, i - 1u, j + 1u);
        }

        if (j != 0u) fill_region(grid, imax, jmax, i, j - 1u);
        if (j != jmax) fill_region(grid, imax, jmax, i, j + 1u);

        if (i != imax) {
            if (j != 0u) fill_region(grid, imax, jmax, i + 1u, j - 1u);
            fill_region(grid, imax, jmax, i + 1u, j);
            if (j != jmax) fill_region(grid, imax, jmax, i + 1u, j + 1u);
        }
    }

    std::size_t fill_and_count_islands(Grid& grid, const std::size_t n,
                                                   const std::size_t m)
    {
        std::size_t count {0u};

        for (std::size_t i {0u}; i != n; ++i) {
            for (std::size_t j {0u}; j != m; ++j) {
                if (grid[i][j]) {
                    fill_region(grid, n - 1u, m - 1u, i, j);
                    ++count;
                }
            }
        }

        return count;
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

        std::cout << fill_and_count_islands(grid, n, m) << '\n';
    }
}
