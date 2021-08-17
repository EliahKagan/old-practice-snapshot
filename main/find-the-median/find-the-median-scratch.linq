<Query Kind="Program" />

internal static class Solution {
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
            if (a[j] < p) a.Swap(lo++, j);

        a.Swap(lo, hi);
        return lo;
    }
    
    private static void Main()
    {
        var r = new Random();
        var a = Enumerable.Range(0, 16).OrderBy(e => r.Next()).ToArray();
        var b = (int[])a.Clone();
        b.LomutoPartition(0, b.Length - 1);
        a.Zip(b, (i, j) => new {i, j}).Dump();
    }
}
