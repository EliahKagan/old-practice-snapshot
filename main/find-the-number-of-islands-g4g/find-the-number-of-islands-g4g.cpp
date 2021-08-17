
namespace {
    void fillRegion(int grid[][MAX], const int imax, const int jmax,
                                     const int i, const int j)
    {
        if (!grid[i][j]) return;
        grid[i][j] = false;

        if (i != 0) {
            if (j != 0) fillRegion(grid, imax, jmax, i - 1, j - 1);
            fillRegion(grid, imax, jmax, i - 1, j);
            if (j != jmax) fillRegion(grid, imax, jmax, i - 1, j + 1);
        }

        if (j != 0) fillRegion(grid, imax, jmax, i, j - 1);
        if (j != jmax) fillRegion(grid, imax, jmax, i, j + 1);

        if (i != imax) {
            if (j != 0) fillRegion(grid, imax, jmax, i + 1, j - 1);
            fillRegion(grid, imax, jmax, i + 1, j);
            if (j != jmax) fillRegion(grid, imax, jmax, i + 1, j + 1);
        }
    }
}

/*you are required to complete this method*/
int findIslands(int grid[][MAX], const int n, const int m)
{
    auto count = 0;

    for (auto i = 0; i != n; ++i) {
        for (auto j = 0; j != m; ++j) {
            if (grid[i][j]) {
                fillRegion(grid, n - 1, m - 1, i, j);
                ++count;
            }
        }
    }

    return count;
}
