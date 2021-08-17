<Query Kind="Program" />

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

internal static class UnitTest {
    private static void Main()
    {
        Test(new[] { new[] { -2, - 3,  3 },
                     new[] { -5, -10,  1 },
                     new[] { 10,  30, -5 } });
        
        Test(new[] { new[] { 0,    0, 0,          0, 0 },
                     new[] { 0,    0, 0,          0, 0 },
                     new[] { 0, 1000, 0,          0, 0 },
                     new[] { 0,    0, 0,          0, 0 },
                     new[] { 0,    0, 0, -1_000_000, 0 },
                     new[] { 0,    0, 0,          0, 0 },
                     new[] { 0,    0, 0,          0, 0 } });

        Test(new[] { new[] { -100, -10, -10_000, -1000 } });
        
        Test(new[] { new[] {    -100 },
                     new[] {     -10 },
                     new[] { -10_000 },
                     new[] {   -1000 } });
    }
    
    private static void Test(int[][] dungeon)
        => new Solution().CalculateMinimumHP(dungeon).Dump("answer");
}
