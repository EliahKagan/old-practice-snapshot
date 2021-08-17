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

        // ensure specified size matches length of list -- but not that it is
        // bijective, since although the question stipulates "you'll be given a
        // permutation", test case #2 inputs the non-permutation (5 1 2 4 3 2)
        Contract.Assert(a.Length == n);

        // follow the permutation twice to check if it is an involution
        var inv = Enumerable.Range(1, a.Length).All(i => a.Get(a.Get(i)) == i);
        Console.WriteLine(inv ? "YES" : "NO");
    }
}
