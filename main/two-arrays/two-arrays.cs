#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Solution {
    /// <summary>
    /// Reads a line as a record, parsing it into integer fields.
    /// </summary>
    /// <returns>The row of numbers received.</returns>
    private static int[] GetRow()
    {
        return Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
    }

    /// <summary>
    /// Reads input for a single test case, runs the test on it, and reports
    /// the result.
    /// </summary>
    private static void Run()
    {
        var nk = GetRow();
        var k = nk[1];
        var n = nk[0];
        Contract.Assert(n >= 0); // purposely broader than given constraint

        var a = GetRow();
        var b = GetRow();
        Contract.Assert(a.Length == n && b.Length == n);

        Array.Sort(a);
        Array.Sort(b);
        Array.Reverse(b);

        while (--n >= 0) {
            if (a[n] + b[n] < k) {
                Console.WriteLine("NO");
                return;
            }
        }

        Console.WriteLine("YES");
    }

    /// <summary>
    /// This entry point method causes the number of runs to be performed that
    /// is specified as the first line of input.
    /// </summary>
    private static void Main()
    {
        foreach (var i in Enumerable.Range(0, int.Parse(Console.ReadLine())))
            Run();
    }
}
