using System;

internal static class Algo {
    private static void Swap(this int[] a, int i, int j)
    {
        var tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    // See https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme
    private static int LomutoPartition(this int[] a, int lo, int hi)
    {
        var p = a[hi];

        for (var j = lo; j < hi; ++j)
            if (a[j] <= p) a.Swap(lo++, j);

        a.Swap(lo, hi);
        Console.WriteLine(string.Join(" ", a));
        return lo;
    }

    private static void Quicksort(this int[] a, int lo, int hi)
    {
        if (lo < hi) {
            var mid = a.LomutoPartition(lo, hi);
            a.Quicksort(lo, mid - 1);
            a.Quicksort(mid + 1, hi);
        }
    }

    internal static void Quicksort(this int[] a)
        => a.Quicksort(0, a.Length - 1);
}

internal static class Solution {
    private static void Main()
    {
        Console.ReadLine(); // don't need n
        Array.ConvertAll(Console.ReadLine().Split(), int.Parse).Quicksort();
    }
}
