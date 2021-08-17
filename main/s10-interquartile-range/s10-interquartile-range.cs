#define DEBUG

using static System.Array;
using static System.Console;
using static System.Diagnostics.Contracts.Contract;
using static System.Linq.Enumerable;

internal static class Solution {
    private static int[] ReadRecord()
            => ConvertAll(ReadLine().Split(' '), int.Parse);

    private static int[] GetDataSet()
    {
        var n = int.Parse(ReadLine());
        var x = ReadRecord();
        var f = ReadRecord();
        Assert(x.Length == n && f.Length == n);

        Sort(x, f);
        return Range(0, n).SelectMany(i => Repeat(x[i], f[i])).ToArray();
    }

    private static double Median(this int[] a, int start, int stop,
                                 out int mid)
    {
        var delta = stop - start;
        mid = start + delta / 2;
        return delta % 2 == 0 ? a[mid] : (a[mid] + a[mid + 1]) / 2.0;
    }

    private static double Median(this int[] a, int start, int stop)
    {
        int mid; // to be discarded
        return a.Median(start, stop, out mid);
    }

    private static void ComputeQuartiles(
            this int[] a, int n, out double q1, out double q2, out double q3)
    {
        int mid;
        q2 = a.Median(0, n - 1, out mid);

        if (n % 2 == 0) {
            q1 = a.Median(0, mid);
            q3 = a.Median(mid + 1, n - 1);
        } else {
            q1 = a.Median(0, mid - 1);
            q3 = a.Median(mid + 1, n - 1);
        }
    }

    private static double InterquartileRange(this int[] a) // assumes a sorted
    {
        double q1, q2, q3;
        a.ComputeQuartiles(a.Length, out q1, out q2, out q3);
        return q3 - q1;
    }

    private static void Main()
            => WriteLine("{0:F1}", GetDataSet().InterquartileRange());
}
