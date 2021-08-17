public class Solution {
    public int IslandPerimeter(int[,] grid) {
        var m = grid.GetLength(0);
        var n = grid.GetLength(1);

        var seams = 0;

        for (var i = 0; i != m; ++i) {
            for (var j = 0; j != n; ++j) {
                if (grid[i, j] == 0) continue;

                if (i == 0 || grid[i - 1, j] == 0) ++seams;
                if (i == m - 1 || grid[i + 1, j] == 0) ++seams;
                if (j == 0 || grid[i, j - 1] == 0) ++seams;
                if (j == n - 1 || grid[i, j + 1] == 0) ++seams;
            }
        }

        return seams;
    }
}
