#define DEBUG

using System;
using System.Diagnostics.Contracts;

internal static class Solution {
    // Returns the median of sorted array a from start to stop, placing the
    // lower midpoint index into mid. Useful for a whole array (if quartiles
    // will later be computed), quartiles (if octiles will later be computed),
    // etc.
    private static int Median(this int[] a, int start, int stop, out int mid)
    {
        var delta = stop - start;
        mid = start + delta / 2;
        return delta % 2 == 0 ? a[mid] : (a[mid] + a[mid + 1]) / 2;
    }

    // Returns the median of sorted array a, placing the lower midpoint index
    // into mid. Use this to compute the median of an array whose quartiles
    // will be subsequently computed.
    private static int Median(this int[] a, out int mid)
            => a.Median(0, a.Length - 1, out mid);

    // Returns median of sorted array a from start to stop.
    // May be used to compute lower/upper quartiles (or octiles, etc.).
    private static int Median(this int[] a, int start, int stop)
    {
        int mid; // to be discarded
        return a.Median(start, stop, out mid);
    }

    // Places the three quartiles of the data in a[0, n) into q1, q2, and q2.
    private static void ComputeQuartiles(this int[] a, int n,
                                         out int q1, out int q2, out int q3)
    {
        int mid;
        q2 = a.Median(out mid);

        if (n % 2 == 0) {
            q1 = a.Median(0, mid);
            q3 = a.Median(mid + 1, n - 1);
        } else {
            q1 = a.Median(0, mid - 1);
            q3 = a.Median(mid + 1, n - 1);
        }
    }

    private static void Main()
    {
        var n = int.Parse(Console.ReadLine());
        var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Contract.Assert(a.Length == n);
        Array.Sort(a);

        int q1, q2, q3;
        a.ComputeQuartiles(n, out q1, out q2, out q3);

        Console.WriteLine(q1);
        Console.WriteLine(q2);
        Console.WriteLine(q3);
    }
}
