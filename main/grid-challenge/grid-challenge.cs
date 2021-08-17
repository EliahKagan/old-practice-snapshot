#define DEBUG

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Solution {
    private static int GetValue()
    {
        return int.Parse(Console.ReadLine());
    }

    private static IEnumerable<int> Range(int count)
    {
        return Enumerable.Range(0, count);
    }

    private static void Run()
    {
        var n = GetValue();
        Contract.Assert(n > 0);

        var a = new char[n][];
        foreach (var i in Range(n)) {
            var row = Console.ReadLine();
            Contract.Assert(row.Length == n);
            a[i] = row.ToCharArray();
            Array.Sort(a[i]);
        }

        foreach (var j in Range(n)) {
            var col = from i in Range(n) select a[i][j];
            var scol = from c in col orderby c select c;

            if (!col.SequenceEqual(scol)) {
                Console.WriteLine("NO");
                return;
            }
        }

        Console.WriteLine("YES");
    }

    private static void Main()
    {
        foreach (var t in Range(GetValue())) Run();
    }
}
