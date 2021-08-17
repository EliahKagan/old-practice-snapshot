#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Solution {
    private static IEnumerable<int> Range(int count)
            => Enumerable.Range(0, count);

    private static int[] ReadRow()
    {
        return Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
    }

    private static int[,] ReadMatrix(int m, int n)
    {
        var matrix = new int[m, n];

        for (var i = 0; i < m; ++i) {
            var row = ReadRow();
            Contract.Assert(row.Length == n);
            for (var j = 0; j < n; ++j) matrix[i, j] = row[j];
        }

        var s = Console.ReadLine();
        Contract.Assert(string.IsNullOrWhiteSpace(s));
        return matrix;
    }

    private static int[] GetShell(this int[,] matrix, int imin, int jmin,
                                                      int imax, int jmax)
    {
        var shell = new int[(imax - imin + jmax - jmin) * 2];
        var k = 0; // index into shell

        var i = imin;
        var j = jmin;

        while (i < imax) shell[k++] = matrix[i++, j];
        while (j < jmax) shell[k++] = matrix[i, j++];
        while (i > imin) shell[k++] = matrix[i--, j];
        while (j > jmin) shell[k++] = matrix[i, j--];

        Contract.Assert(k == shell.Length);
        return shell;
    }

    private static int[] Cycle(this int[] shell, int r)
    {
        var len = shell.Length;
        var cycled = new int[len];
        r %= len;

        var j = 0;  // index into image (cycled)

        var i = r;  // index into pre-image (shell)
        while (i < len) cycled[i++] = shell[j++];

        i = 0;
        while (i < r) cycled[i++] = shell[j++];

        Contract.Assert(j == len);
        return cycled;
    }

    private static void PutShell(this int[,] matrix, int[] shell,
                                 int imin, int jmin, int imax, int jmax)
    {
        var k = 0; // index into shell

        var i = imin;
        var j = jmin;

        while (i < imax) matrix[i++, j] = shell[k++];
        while (j < jmax) matrix[i, j++] = shell[k++];
        while (i > imin) matrix[i--, j] = shell[k++];
        while (j > jmin) matrix[i, j--] = shell[k++];

        Contract.Assert(k == shell.Length);
    }

    private static int[,] CycleAll(this int[,] matrix, int depth, int r,
                                   int imin, int jmin, int imax, int jmax)
    {
        for (; depth > 0; --depth, ++imin, ++jmin, --imax, --jmax) {
            matrix.PutShell(matrix.GetShell(imin, jmin, imax, jmax).Cycle(r),
                            imin, jmin, imax, jmax);
        }

        return matrix;
    }

    private static void Print(this int[,] matrix, int m, int n)
    {
        var jmax = n - 1;
        var jrange = Range(jmax);

        foreach (var i in Range(m)) {
            foreach (var j in jrange) Console.Write("{0} ", matrix[i, j]);
            Console.WriteLine(matrix[i, jmax]);
        }
    }

    private static void Main()
    {
        var mnr = ReadRow();
        var m = mnr[0];
        var n = mnr[1];
        var r = mnr[2];
        Contract.Assert(m > 1 && n > 1 && r > 0);

        int stationary_kernel;
        var depth = Math.DivRem(Math.Min(m, n), 2, out stationary_kernel);
        Contract.Assert(stationary_kernel == 0, "need min(M, N) % 2 == 0");

        ReadMatrix(m, n).CycleAll(depth, r, 0, 0, m - 1, n - 1).Print(m, n);
    }
}
