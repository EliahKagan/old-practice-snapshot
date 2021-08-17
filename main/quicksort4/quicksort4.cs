using System;

internal static class Algo {
    private static void Swap(this int[] a, int i, int j, ref int swaps)
    {
        var tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
        
        ++swaps;
    }

    // See https://en.wikipedia.org/wiki/Quicksort#Lomuto_partition_scheme
    private static int LomutoPartition(this int[] a, int lo, int hi,
                                       ref int swaps)
    {
        var p = a[hi];

        for (var j = lo; j < hi; ++j)
            if (a[j] < p) a.Swap(lo++, j, ref swaps);

        a.Swap(lo, hi, ref swaps);
        return lo;
    }

    private static void Quicksort(this int[] a, int lo, int hi, ref int swaps)
    {   
        if (lo < hi) {
            var mid = a.LomutoPartition(lo, hi, ref swaps);
            a.Quicksort(lo, mid - 1, ref swaps);
            a.Quicksort(mid + 1, hi, ref swaps);
        }
    }

    internal static int Quicksort(this int[] a) // returns number of swaps
    {
        var swaps = 0;
        a.Quicksort(0, a.Length - 1, ref swaps);
        return swaps;
    }
    
    internal static int InsertionSort(this int[] a) // returns number of shifts
    {
        var shifts = 0;

        for (var size = 2; size <= a.Length; ++size) {
            var i = size - 1;
            var e = a[i];

            for (; 0 < i && e < a[i - 1]; --i, ++shifts)
                a[i] = a[i - 1];

            a[i] = e;
        }

        return shifts;
    }
}

internal static class Solution {
    private static void Main()
    {
        Console.ReadLine(); // don't need n
        
        var a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        var b = (int[])a.Clone();
        
        Console.WriteLine(a.InsertionSort() - b.Quicksort());
    }
}
