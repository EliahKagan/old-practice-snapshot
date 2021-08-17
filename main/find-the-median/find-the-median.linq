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
    
    private static int FindMedian(this int[] a) // permutes a
    {
        var half = a.Length / 2;
        
        var lo = 0;
        var hi = a.Length - 1;
        
        for (int mid; (mid = a.LomutoPartition(lo, hi)) != half; ) {
            if (mid < half) lo = mid + 1;
            else            hi = mid - 1;
        }
        
        return a[half];
    }
    
    private static void Main()
        => Array.ConvertAll(Console.ReadLine().Split(), int.Parse)
                .FindMedian()
                .Dump();
}
