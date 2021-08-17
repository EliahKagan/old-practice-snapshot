#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <iostream>
#include <vector>

namespace {
    enum { blank_wall, source, destination, blank_cell };

    using Grid = std::vector<std::vector<int>>;

    std::vector<int> get_row(std::size_t n)
    {
        std::vector<int> row;
        row.reserve(n);

        while (n-- != 0u) {
            auto e = 0;
            std::cin >> e;
            row.push_back(e);
        }

        return row;
    }

    Grid get_grid()
    {
        std::size_t n{};
        std::cin >> n;
        assert(n != 0u);

        std::vector<std::vector<int>> grid;
        grid.reserve(n);

        for (auto i = n; i != 0u; --i) grid.push_back(get_row(n));
        return grid;
    }

    bool find_source(const Grid& grid, std::size_t& r, std::size_t& c)
    {
        for (std::size_t i{0u}; i != grid.size(); ++i) {
            for (std::size_t j{0u}; j != grid.size(); ++j) {
                if (grid[i][j] == source) {
                    r = i;
                    c = j;
                    return true;
                }
            }
        }

        return false;
    }

    void debug_grid(const Grid& grid)
    {
        for (std::size_t i {0u}; i != grid.size(); ++i) {
            for (std::size_t j{0u}; j != grid.size(); ++j)
                std::cerr << ' ' << grid[i][j];

            std::cerr << '\n';
        }
    }

    bool dfs(Grid& grid, const std::size_t i, const std::size_t j)
    {
        debug_grid(grid);

        switch (grid[i][j]) {
        case blank_wall:
            return false;

        case destination:
            return true;
        
        default:
            grid[i][j] = blank_wall;
            
            const auto m = grid.size() - 1u;
                
            return (i != 0u && dfs(grid, i - 1u, j))
                    || (i != m && dfs(grid, i + 1u, j))
                    || (j != 0u && dfs(grid, i, j - 1u))
                    || (j != m && dfs(grid, i, j + 1u));
        }
    }
    
    bool path_exists(Grid& grid)
    {
        std::size_t i {}, j {};
        return find_source(grid, i, j) && dfs(grid, i, j);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto grid = get_grid();
        std::cout << path_exists(grid) << '\n';
    }
}
