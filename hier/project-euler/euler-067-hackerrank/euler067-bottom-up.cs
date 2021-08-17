using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    private static IEnumerable<int> ReadValAsRange() =>
        Enumerable.Range(0, int.Parse(Console.ReadLine()));
    
    private static int[] ReadRow() =>
        Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
    
    private static int[][] ReadGrid() =>
        ReadValAsRange().Select(_ => ReadRow()).ToArray();
    
    private static int MaxSumBottomUp(this int[][] grid) // mutates grid
    {
        for (var i = grid.Length - 2; i >= 0; --i) {
            for (var j = i; j >= 0; --j)
                grid[i][j] += Math.Max(grid[i + 1][j], grid[i + 1][j + 1]);
        }
        
        return grid[0][0];
    }
    
    private static void Main()
    {
        foreach (var t in ReadValAsRange())
            Console.WriteLine(ReadGrid().MaxSumBottomUp());
    }
}
