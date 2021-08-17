public class Solution {
    public int MaxAreaOfIsland(int[,] grid) {
        var m = grid.GetLength(0);
        var n = grid.GetLength(1);

        int Sink(int i, int j) {
            if (i == -1 || i == m || j == -1 || j == n || grid[i, j] == 0)
                return 0;

            grid[i, j] = 0;

            return 1 + Sink(i - 1, j) + Sink(i + 1, j)
                     + Sink(i, j - 1) + Sink(i, j + 1);
        }

        var max = 0;
        for (var i = 0; i != m; ++i) {
            for (var j = 0; j != n; ++j)
                max = Math.Max(max, Sink(i, j));
        }

        return max;
    }
}
