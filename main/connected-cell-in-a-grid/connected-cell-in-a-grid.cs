using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Geometry {
    private static IEnumerable<int> ConnectedAreas(int[][] a, int m, int n)
    {
        var imax = m - 1;
        var jmax = n - 1;
    
        var s = Array.ConvertAll(a, row => row.Sum());
        for (var k = 0; (k = Array.FindIndex(s, k, sum => sum != 0)) != -1; ) {
            var area = 0;
        
            var q = new Queue<Tuple<int, int>>();
            Action<int, int> enq = (i, j) => q.Enqueue(Tuple.Create(i, j));
            enq(k, Array.IndexOf(a[k], 1));
        
            do {
                var ij = q.Dequeue();
                var i = ij.Item1;
                var j = ij.Item2;
            
                if (a[i][j] != 1) continue; // in case i,j was enqueued twice
            
                a[i][j] = 0;
                --s[i];
                ++area;
            
                if (i != 0 && a[i - 1][j] == 1) enq(i - 1, j);
                if (i != imax && a[i + 1][j] == 1) enq(i + 1, j);
                if (j != 0 && a[i][j - 1] == 1) enq(i, j - 1);
                if (j != jmax && a[i][j + 1] == 1) enq(i, j + 1);
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
