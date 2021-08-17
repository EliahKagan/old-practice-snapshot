using System;
using System.Collections.Generic;

internal static class Solution {
    private static int CountBeautifulTriplets(int[] a, int d)
    {
        var count = 0;
        
        var d2 = d * 2;
        var s = new HashSet<int>(a);
        
        foreach (var x in a)
            if (s.Contains(x + d) && s.Contains(x + d2)) ++count;
        
        return count;
    }
    
    private static void Main()
    {
        var d = int.Parse(Console.ReadLine().Split()[1]); // don't need n
        var a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        Console.WriteLine(CountBeautifulTriplets(a, d));
    }
}
