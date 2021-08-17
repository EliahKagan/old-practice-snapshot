public class Solution {
    public int NumIslands(char[,] grid) {
        var m = grid.GetLength(0);
        var n = grid.GetLength(1);

        void Sink(int i, int j) {
            if (i != -1 && i != m && j != -1 && j != n && grid[i, j] != '0') {
                grid[i, j] = '0';

                Sink(i - 1, j);
                Sink(i + 1, j);
                Sink(i, j - 1);
                Sink(i, j + 1);
            }
        }

        var count = 0;

        for (var i = 0; i != m; ++i) {
            for (var j = 0; j != n; ++j) {
                if (grid[i, j] != '0') {
                    Sink(i, j);
                    ++count;
                }
            }
        }

        return count;
    }
}
