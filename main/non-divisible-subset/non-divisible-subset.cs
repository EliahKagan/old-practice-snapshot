using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static IEnumerable<int> ReadRecord()
        => Console.ReadLine().Split().Select(int.Parse);
    
    private static int[] GetFrequenciesMod(this IEnumerable<int> values, int k)
    {
        var counts = new int[k]; // frequencies (mod k) of each value
        foreach (var x in values) ++counts[x % k];
        return counts;
    }
    
    private static void Main()
    {
        var k = ReadRecord().Last(); // don't need n
        var counts = ReadRecord().GetFrequenciesMod(k);
        
        var cardinality = 0; // max subset with no partial sums divisible by k
        
        var i = 1;
        var j = k - 1;
        
        // include the larger of each complementary pair of subsets
        while (i < j) cardinality += Math.Max(counts[i++], counts[j--]);
        
        // the 0 and k / 2 self-complements contribute at most one value each
        if (i == j && counts[i] != 0) ++cardinality;
        if (counts[0] != 0) ++cardinality;
        
        Console.WriteLine(cardinality);
    }
}
