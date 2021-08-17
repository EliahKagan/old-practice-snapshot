using System;
using System.Linq;

internal static class Solution {
    private static int[] GetElementsWithSentinel()
    {
        Console.ReadLine(); // don't need n
        
        return Console.ReadLine().Split()
                                 .Select(int.Parse)
                                 .OrderBy(ai => ai)
                                 .Concat(Enumerable.Repeat(int.MaxValue, 1))
                                 .ToArray();
    }
    
    private static void Main()
    {
        var a = GetElementsWithSentinel();
        
        var best = 1;
        var cur = 1;
        
        foreach (var i in Enumerable.Range(1, a.Length - 1)) {
            if (Math.Abs(a[i] - a[i - 1]) > 1) {
                if (best < cur) best = cur;
                cur = 1;
            }
            else ++cur;
        }
        
        Console.WriteLine(best);
    }
}
