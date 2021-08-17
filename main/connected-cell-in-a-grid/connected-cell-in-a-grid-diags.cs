using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("0.2.1.0")]

internal static class Geometry {
    private static IEnumerable<int> ConnectedAreas(int[][] a, int m, int n)
    {
        Func<int, int, bool> got = (i, j) =>
            0 <= i && i < m && 0 <= j && j < n && a[i][j] == 1;

        var s = Array.ConvertAll(a, row => row.Sum());
        for (var k = 0; (k = Array.FindIndex(s, k, sum => sum != 0)) != -1; ) {
            var area = 0;
            var q = new Queue<Tuple<int, int>>();
            
            Action<int, int> enq = (i, j) => q.Enqueue(Tuple.Create(i, j));
            Action<int, int> proxenq = (i, j) => { if (got(i, j)) enq(i, j); };

            enq(k, Array.IndexOf(a[k], 1));
            do {
                var ij = q.Dequeue();
                var i = ij.Item1;
                var j = ij.Item2;
            
                if (a[i][j] != 1) continue; // in case i,j is multiply enqueued
            
                a[i][j] = 0;
                --s[i];
                ++area;

                proxenq(i - 1, j - 1);
                proxenq(i - 1, j);
                proxenq(i - 1, j + 1);
                proxenq(i, j - 1);
                proxenq(i, j + 1);
                proxenq(i + 1, j - 1);
                proxenq(i + 1, j);
                proxenq(i + 1, j + 1);
            }
            while (q.Count != 0);
        
            yield return area;
        }
    }

    internal static int MaxConnectedArea(int[][] a, int m, int n)
            => ConnectedAreas(a, m, n).DefaultIfEmpty().Max();
}

internal static class Solution {
    private static int GetValue() => int.Parse(Console.ReadLine());

    private static int[] GetRow(int n)
    {
        var row = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Contract.Assert(row.Length == n);
        return row;
    }

    private static int[][] GetMatrix(int m, int n)
    {
        var a = new int[m][];
        foreach (var i in Enumerable.Range(0, m)) a[i] = GetRow(n);
        return a;
    }

    private static void Main()
    {
        var m = GetValue();
        var n = GetValue();
        Console.WriteLine(Geometry.MaxConnectedArea(GetMatrix(m, n), m, n));
    }
}
