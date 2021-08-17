using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static int[] CountingSortCounts(IEnumerable<int> values)
    {
        var counts = new int[100];
        foreach (var i in values) ++counts[i];
        return counts;
    }
    
    private static IEnumerable<int> CountingSortTotals(IEnumerable<int> values)
    {
        var s = 0;
        foreach (var i in CountingSortCounts(values)) yield return s += i;
    }
    
    private static IEnumerable<int> ReadValues()
    {
        for (var n = int.Parse(Console.ReadLine()); n > 0; --n)
            yield return int.Parse(Console.ReadLine().Split()[0]);
    }
    
    private static void Main()
        => Console.WriteLine(string.Join(" ",
                                         CountingSortTotals(ReadValues())));
}
