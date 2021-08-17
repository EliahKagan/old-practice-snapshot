using System;
using System.Collections.Generic;

internal static class Solution {
    private static List<int> GetBestPairs(int[] a, int n)
    {
        var best = int.MaxValue;
        var pairs = new List<int>();
        
        var i = 0;
        for (var j = 1; j != n; ++i, ++j) {
            var cur = a[j] - a[i];
            if (best < cur) continue;
            
            if (best != cur) {
                best = cur;
                pairs.Clear();
            }
            
            pairs.Add(a[i]);
            pairs.Add(a[j]);
        }
        
        return pairs;
    }
    
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        Array.Sort(a);
        
        Console.WriteLine(string.Join(" ", GetBestPairs(a, n)));
    }
}
