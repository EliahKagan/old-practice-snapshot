using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static int GetMinCost(this IEnumerable<int> weights)
    {
        const int window = 4; // 0, 1, 2, 3, 4
        var threshold = int.MinValue;
        var count = 0;
        
        foreach (var w in weights) {
            if (threshold < w) {
                threshold = w + window;
                ++count;
            }
        }
        
        return count;
    }
    
    private static void Main()
    {
        Console.ReadLine(); // don't need n
        
        Console.WriteLine(Console.ReadLine().Split().Select(int.Parse)
                                                    .OrderBy(x => x)
                                                    .GetMinCost());
    }
}
