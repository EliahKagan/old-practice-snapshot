using System;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        Array.Sort(a);
        
        var best = int.MaxValue;
        
        var i = 0;
        for (var j = 1; j != n; ++i, ++j) {
            var cur = a[j] - a[i];
            if (best > cur) best = cur;
        }
        
        Console.WriteLine(best);
    }
}
