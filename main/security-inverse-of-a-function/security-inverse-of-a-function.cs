#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Program {
    private static int Get(this int[] self, int i)
    {
        return self[i - 1];
    }

    private static void Set(this int[] self, int i, int n)
    {
        self[i - 1] = n;
    }

    private static void Main()
    {
        // read n and f(1), f(2), ..., f(n)
        var n = int.Parse(Console.ReadLine());
        var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

        // ensure the correct number of data were read and f is bijective
        Contract.Assert(1 <= n && n <= 20 && a.Length == n);
        Contract.Assert(Enumerable.Range(1, n).Intersect(a).Count() == n);

        // build the inverse array (where a represents f, b represents f^-1)
        var b = new int[n];
        foreach (var k in Enumerable.Range(1, n))
            b.Set(a.Get(k), k);

        Array.ForEach(b, Console.WriteLine);
    }
}
