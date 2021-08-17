using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

internal static class Solution {
    private static int ReadValue() => int.Parse(Console.ReadLine());
    
    private static int[] ReadRow(int n)
    {
        var row = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        Trace.Assert(row.Length == n);
        return row;
    }
    
    private static int[][] ReadMatrix()
    {
        var n = ReadValue();
        return Enumerable.Range(0, n).Select(_ => ReadRow(n)).ToArray();
    }
    
    private static IEnumerable<int> RowSums(this int[][] self)
        => self.Select(Enumerable.Sum);
    
    private static IEnumerable<int> ColSums(this int[][] self)
    {
        for (var i = 0; i != self.Length; ++i)
            yield return self.Select(row => row[i]).Sum();
    }
    
    private static void Main()
    {
        for (var t = ReadValue(); t > 0; --t) {
            var matrix = ReadMatrix();
            
            // We need the bag of container sizes (number of balls in each
            // container) to be equal to the bag of color counts (number of
            // balls of each color).
            var container_sizes = matrix.RowSums().OrderBy(x => x);
            var color_counts = matrix.ColSums().OrderBy(x => x);
            var possible = container_sizes.SequenceEqual(color_counts);
            
            Console.WriteLine(possible ? "Possible" : "Impossible");
        }
    }
}
