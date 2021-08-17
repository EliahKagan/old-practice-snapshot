public class Solution {
    public int CalculateMinimumHP(int[][] dungeon)
    {
        var m = dungeon.Length;
        var n = dungeon[0].Length;
        var dp = new int[n];

        // lower-right corner
        dp[n - 1] = Math.Max(1, 1 - dungeon[m - 1][n - 1]);

        // rest of bottom row - must always go right
        for (var j = n - 2; j >= 0; --j)
            dp[j] = Math.Max(1, dp[j + 1] - dungeon[m - 1][j]);

        // other rows (above the bottom row)
        for (var i = m - 2; i >= 0; --i) {
            // rightmost column position - must always go down
            dp[n - 1] = Math.Max(1, dp[n - 1] - dungeon[i][n - 1]);

            // other column positions - may go right or down
            for (var j = n - 2; j >= 0; --j) {
                dp[j] = Math.Max(1, Math.Min(dp[j + 1], dp[j])
                                        - dungeon[i][j]);
            }
        }

        return dp[0];
    }
}
