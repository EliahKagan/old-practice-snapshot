#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class Solution {
    private static int GetNumber() => int.Parse(Console.ReadLine());

    private static int ComputeSignature(int?[] a) // note: destroys data in a
    {
        var sig = 1;

        for (var i = 1;  (i = Array.FindIndex(a, i, k => k.HasValue)) >= 0; ) {
            var len = 0; // easier to debug a per-cycle length than a signature

            int? current = i;
            do {
                ++len;
                var next = a[current.Value];
                a[current.Value] = null;
                current = next;
            }
            while (current.HasValue);

            if (len % 2 != 0) sig *= -1;
        }

        return sig;
    }

    private static void Main()
    {
        var replies = new Dictionary<int, string> // answer strings, indexed by
                { { 1, "YES" }, { -1, "NO" } };   // signature of permutation

        var null_singleton = Enumerable.Repeat((int?)null, 1);

        foreach (var t in Enumerable.Range(0, GetNumber())) {
            var n = GetNumber();
            var record = Console.ReadLine().Split(' ').Select(int.Parse);
            var a = null_singleton.Concat(record.Cast<int?>()).ToArray();
            Contract.Assert(a.Length == n + 1);

            Console.WriteLine(replies[ComputeSignature(a)]);
        }
    }
}
