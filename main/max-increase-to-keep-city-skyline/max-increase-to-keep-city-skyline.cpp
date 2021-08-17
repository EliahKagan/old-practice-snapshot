class Solution {
public:
    static int maxIncreaseKeepingSkyline(const vector<vector<int>>& grid);
};

namespace {
    int max_in_row(const vector<vector<int>>& grid, const size_t i)
    {
        // Assumes grid[i] is nonempty.
        return *max_element(cbegin(grid[i]), cend(grid[i]));
    }
    
    int max_in_col(const vector<vector<int>>& grid, const size_t j)
    {
        auto acc = numeric_limits<int>::min();
        for (const auto& row : grid) acc = max(acc, row[j]);
        return acc;
    }
}

int Solution::maxIncreaseKeepingSkyline(const vector<vector<int>>& grid)
{
    assert(!grid.empty());
    const auto m = grid.size(), n = grid[0].size();
    
    vector<int> row_maxima (m);
    for (size_t i {0}; i != m; ++i) row_maxima[i] = max_in_row(grid, i);
    
    vector<int> col_maxima (n);
    for (size_t j {0}; j != n; ++j) col_maxima[j] = max_in_col(grid, j);
    
    auto acc = 0;
    for (size_t i {0}; i != m; ++i) {
        for (size_t j {0}; j != n; ++j) {
            const auto maximum = min(row_maxima[i], col_maxima[j]);
            acc += max(0, maximum - grid[i][j]);
        }
    }
    
    return acc;
}
