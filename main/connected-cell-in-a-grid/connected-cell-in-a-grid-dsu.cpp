#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace {
    class DisjointSets {
    public:
        // Perform `size` makeset operations.
        explicit DisjointSets(int size);
        
        // Union by size with path compression.
        void unite(int i, int j) noexcept;
        
        // Obtain the number of elements in the largest set.
        int max_cardinality() const noexcept;
    
    private:
        static int check_size(int size);
        
        int find_set(int i) noexcept;
        
        // Stores a negated size (negative), or a parent index (nonnegative).
        std::vector<int> elems_;
    };
    
    DisjointSets::DisjointSets(const int size) : elems_(check_size(size), -1)
    {
    }
    
    void DisjointSets::unite(int i, int j) noexcept
    {
        // find the ancestors and stop if they are already the same
        i = find_set(i);
        j = find_set(j);
        if (i == j) return;
        
        // perform union by size with full path compression
        if (elems_[i] > elems_[j]) {
            // the set with i is smaller; use j as the representative
            elems_[j] += elems_[i];
            elems_[i] = j;
        } else {
            // the set with i is at least as big; use i as the representative
            elems_[i] += elems_[j];
            elems_[j] = i;
        }
    }
    
    int DisjointSets::max_cardinality() const noexcept
    {
        assert(!elems_.empty());
        return -*min_element(cbegin(elems_), cend(elems_));
    }
    
    int DisjointSets::check_size(const int size)
    {
        if (size <= 0)
            throw std::length_error{"must have at least one element"};
        
        return size;
    }
    
    int DisjointSets::find_set(int i) noexcept
    {
        // find the ancestor
        auto j = i;
        while (elems_[j] >= 0) j = elems_[j];
        
        // compress the path
        while (i != j) {
            const auto parent = elems_[i];
            elems_[i] = j;
            i = parent;
        }
        
        return j;
    }
    
    using Grid = std::vector<std::vector<int>>;
    
    Grid read_grid(const int n, const int m)
    {
        Grid grid (n, std::vector<int>(m));
        
        for (auto& row : grid)
            for (auto& cell : row) std::cin >> cell;
        
        return grid;
    }
    
    int mark_grid(Grid& grid) // returns area
    {
        auto area = 0;
        
        for (auto& row : grid) {
            for (auto& cell : row)
                if (cell != 0) cell = ++area;
        }
        
        return area;
    }
    
    void try_connect(DisjointSets& sets, const Grid& grid,
                     const int i, const int j, const int ii, const int jj)
    {
        if (ii < 0 || jj < 0) return;
        
        const auto elem = grid[ii][jj];
        if (elem != 0) sets.unite(grid[i][j], elem);
    }
    
    // Obtains the maximum area of the grid. Assumes this area is at least 1.
    int max_area(const int n, const int m, Grid&& grid)
    {
        const auto area = mark_grid(grid);
        if (area == 0) return 0;
        
        DisjointSets sets {area + 1}; // +1 for 1-based indexing
        
        for (auto i = 0; i != n; ++i) {
            for (auto j = 0; j != m; ++j) {
                if (grid[i][j] == 0) continue;
                
                try_connect(sets, grid, i, j, i - 1, j - 1);
                try_connect(sets, grid, i, j, i - 1, j);
                try_connect(sets, grid, i, j, i - 1, j + 1);
                try_connect(sets, grid, i, j, i, j - 1);
            }
        }
        
        return sets.max_cardinality();
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n, m {};
    std::cin >> n >> m;
    auto grid = read_grid;
    
    std::cout << max_area(n, m, read_grid(n, m)) << '\n';
}
