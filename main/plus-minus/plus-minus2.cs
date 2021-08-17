#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Solution {
    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var s = (double)n;

        var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Contract.Assert(a.Length == n, "row not of specified length");

        var nzp = new int[3];
        foreach (var value in a) ++nzp[Math.Sign(value) + 1];

        foreach (var count in new[] { nzp[2], nzp[0], nzp[1] })
            Console.WriteLine("{0:F6}", count / s);
    }
}
