#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Linq;

internal static class Solution {
    private static int Get(this int[] self, int i)
    {
        return self[i - 1];
    }

    private static void Main()
    {
        // read size for permutation, then permutation as list of values
        var n = int.Parse(Console.ReadLine());
        var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

        // ensure specified size matches length of list and list is bijective
        Contract.Assert(a.Length == n);
        Contract.Assert(Enumerable.Range(1, n).Intersect(a).Count() == n);

        // follow the permutation twice and print each result
        foreach (var val in a)
            Console.WriteLine(a.Get(val));
    }
}
