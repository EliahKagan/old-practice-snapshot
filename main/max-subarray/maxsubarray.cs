using System;
using System.Collections.Generic;
using System.Linq;

internal static class Algo {
    internal static int Kadane(this int[] a)
    {
        var cur = a[0];
        var best = cur;
        
        for (var i = 1; i != a.Length; ++i) {
            cur = Math.Max(cur + a[i], a[i]);
            best = Math.Max(best, cur);
        }
        
        return best;
    }
    
    internal static int MaxSubSum(this IEnumerable<int> xs)
        => xs.Where(x => x > 0).DefaultIfEmpty(xs.Max()).Sum();
}

internal static class Solution {
    private static int GetOne() => int.Parse(Console.ReadLine());
    
    private static int[] GetMany()
        => Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
    
    private static void Main()
    {
        for (var t = GetOne(); t > 0; --t) {
            Console.ReadLine(); // don't need n
            var a = GetMany();
            
            Console.WriteLine($"{a.Kadane()} {a.MaxSubSum()}");
        }
    }
}
