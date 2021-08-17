#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Solution {
    private static IEnumerable<int> Range(int n)
    {
        return Enumerable.Range(0, n);
    }

    private static int DiagonalDifference(int[][] a)
    {
        var n = a.Length;
        Contract.Assert(a.All(row => row.Length == n));

        var primary = Range(n).Sum(i => a[i][i]);
        var secondary = Range(n).Sum(i => a[i][n - i - 1]);
        return Math.Abs(primary - secondary);
    }

    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var a = new int[n][];

        foreach (var i in Range(n)) {
            var line = Console.ReadLine();
            a[i] = line.Split(' ').Select(int.Parse).Take(n).ToArray();
        }

        Console.WriteLine(DiagonalDifference(a));
    }
}
