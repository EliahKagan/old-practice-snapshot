<Query Kind="Program" />

public class Solution {
    public int CalculateMinimumHP(int[][] dungeon)
    {
        var low = 1L;
        var high = (long)int.MaxValue; // FIXME: use better estimate
        
        while (low != high) {
            var mid = low + (high - low) / 2L;
            
            if (CanReach(dungeon, mid))
                high = mid;
            else
                low = mid + 1;
        }
        
        return (int)low;
    }
    
    private static bool CanReach(int[][] dungeon, long initialHealth)
    {
        var m = dungeon.Length;
        var n = dungeon[0].Length;
        var dp = new long[n];
        
        // upper-left corner
        dp[0] = initialHealth + dungeon[0][0];
        if (dp[0] <= 0L) return false;
        
        // rest of top row
        for (var j = 1; j != n; ++j) {
            // must use value from the left, and we've already checked
            dp[j] = Math.Max(0L, dp[j - 1] + dungeon[0][j]);
            
            // stop when we can't go further
            if (dp[j] == 0) break;
        }
        
        dp.Dump("DP row 0");
        
        // subsequent rows
        for (var i = 1; i != m; ++i) {
            // leftmost element - must use value from above
            if (dp[0] != 0L)
                dp[0] = Math.Max(0L, dp[0] + dungeon[i][0]);
            
            // remaining elements in row
            for (var j = 1; j != n; ++j) {
                // try value from above
                if (dp[j] != 0L)
                    dp[j] = Math.Max(0L, dp[j] + dungeon[i][j]);
                
                // try value from left
                if (dp[j - 1] != 0L)
                    dp[j] = Math.Max(dp[j], dp[j - 1] + dungeon[i][j]);
            }
            
            dp.Dump($"DP row {i}");
        }
        
        return dp[n - 1] != 0L;
    }
    
    private static void Main()
    {
        var dungeon = new int[][] { new int[] { -2, - 3,  3 },
                                    new int[] { -5, -10,  1 },
                                    new int[] { 10,  30, -5 } };
        
        //for (var initialHealth = 1L; initialHealth <= 10; ++initialHealth)
        //    CanReach(dungeon, initialHealth).Dump($"{initialHealth}");
        
        CanReach(dungeon, 7).Dump();
        CanReach(dungeon, 8).Dump();
    }
}
