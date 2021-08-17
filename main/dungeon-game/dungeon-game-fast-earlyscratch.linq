<Query Kind="Program" />

public class Solution {
    public int CalculateMinimumHP(int[][] dungeon)
    {
        var m = dungeon.Length;
        var n = dungeon[0].Length;
        var dp = new int[n];
        
        // lower-right corner
        dp[n - 1] = 1 - Math.Min(0, dungeon[m - 1][n - 1]);
        
        // rest of bottom row - must always go right
        for (var j = n - 2; j != -1; --j) {
            dp[j] = 
        }
        
    }
}