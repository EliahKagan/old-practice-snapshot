using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static IEnumerable<int> CountingSort(this IEnumerable<int> values)
    {
        var counts = new int[100];
        foreach (var i in values) ++counts[i];
        
        for (var i = 0; i != counts.Length; ++i)
            while (counts[i]-- != 0) yield return i;
    }
    
    private static void Main()
    {
        Console.ReadLine(); // don't need n
        
        Console.WriteLine(string.Join(" ", Console.ReadLine().Split()
                                                  .Select(int.Parse)
                                                  .CountingSort()));
    }
}
