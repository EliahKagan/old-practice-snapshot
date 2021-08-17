using System;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var values = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
        var indices = Enumerable.Range(0, n).ToArray();
        Array.Sort(values, indices);
        
        var best = long.MaxValue;
        
        for (var i = 0; i != n; ++i) {
            var j = i + 1;
            while (j != n && indices[i] < indices[j]) ++j;
            if (j == n) continue;
            
            var cur = values[j] - values[i];
            if (best > cur) best = cur;
        }
        
        Console.WriteLine(best);
    }
}
