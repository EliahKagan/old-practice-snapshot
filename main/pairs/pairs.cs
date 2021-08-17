#define DEBUG

using System;
using System.Diagnostics.Contracts;

internal static class Solution {
    // Counts pairs of integers in a that subtract to produce the value k.
    private static int CountPairs(int[] a, int k) // note: mutates a
    {
        Array.Sort(a);
        var count = 0;

        var stop = a.Length - 1;
        for (var i = 0; i < stop; ++i) {
            if (Array.BinarySearch(a, i + 1, stop - i, a[i] + k) >= 0)
                ++count;
        }

        return count;
    }
    
    private static int[] GetRecord(int length)
    {
        var vals = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Contract.Assert(vals.Length == length);
        return vals;
    }

    private static void Main()
    {
        var nk = GetRecord(2);
        var a = GetRecord(nk[0]);
        Console.WriteLine(CountPairs(a, nk[1]));
    }
}
