public class Solution {
    public int MinPathSum(int[,] grid) {
        var m = grid.GetLength(0);
        var n = grid.GetLength(1);

        for (var i = 1; i != m; ++i) grid[i, 0] += grid[i - 1, 0];
        for (var j = 1; j != n; ++j) grid[0, j] += grid[0, j - 1];

        for (var i = 1; i != m; ++i) {
            for (var j = 1; j != n; ++j)
                grid[i, j] += Math.Min(grid[i - 1, j], grid[i, j - 1]);
        }

        return grid[m - 1, n - 1];
    }
}
