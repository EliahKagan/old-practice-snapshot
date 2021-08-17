public class Solution {
    public int UniquePathsWithObstacles(int[,] obs) {
        const int free = 0; // indicates the ABSENCE of an obstacle in obs
        if (obs[0, 0] != free) return 0;

        var m = obs.GetLength(0);
        var n = obs.GetLength(1);
        var paths = new int[m, n];

        paths[0, 0] = 1;
        for (var i = 1; i != m && obs[i, 0] == free; ++i) paths[i, 0] = 1;
        for (var j = 1; j != n && obs[0, j] == free; ++j) paths[0, j] = 1;

        for (var i = 1; i != m; ++i) {
            for (var j = 1; j != n; ++j) {
                if (obs[i, j] == free)
                    paths[i, j] = paths[i - 1, j] + paths[i, j - 1];
            }
        }

        return paths[m - 1, n - 1];
    }
}
