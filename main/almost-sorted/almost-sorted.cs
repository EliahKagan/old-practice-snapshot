#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Solution {
    // Helper function for GetResult().
    private static string[] MakeResult(string op, params int[] args)
    {
        if (args.Length == 0) return new[] { op }; // then op is "yes" or "no"
        return new[] { "yes", $"{op} {args[0] + 1} {args[1] + 1}" };
    }

    // Gets the result for output; e must be a permutation of length n.
    private static string[] GetResult(int[] e, int n)
    {
        var h = 0; // find first non-increasing element
        for (; ; ++h) {
            if (h == n) return MakeResult("yes");
            if (e[h] != h) break;
        }

        var i = h + 1; // find first non-decreasing element after h
        while (i != n && e[i - 1] - e[i] == 1) ++i;

        for (var j = i; ; ++j) { // find first non-increasing element after i
            if (j == n)
                return MakeResult((i - h == 2 ? "swap" : "reverse"), h, i - 1);

            if (e[j] != j) break;
        }

        // check if any but one pair [at (h, e[h])] are increasing
        for (var k = h + 1; k != n; ++k) {
            if (!(e[k] == k || (k == e[h] && e[k] == h)))
                return MakeResult("no");
        }

        return MakeResult("swap", h, e[h]);
    }

    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var d = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Contract.Assert(d.Length == n);

        var e = Enumerable.Range(0, n).ToArray();
        Array.Sort(d, e);

        foreach (var line in GetResult(e, n)) Console.WriteLine(line);
    }
}
