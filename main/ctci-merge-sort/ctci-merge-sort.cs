using System;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Algo {
    private static long Merge(this int[] a, int[] aux, int lo, int hi)
    {
        var mid = lo + (hi - lo) / 2;

        var i = lo;
        var j = mid + 1;
        var k = lo;
        
        var swaps = 0L;
        while (i <= mid && j <= hi) { // merge from left and right sides
            if (a[i] <= a[j]) aux[k++] = a[i++];
            else {
                swaps += j - k;
                aux[k++] = a[j++];
            }
        }

        while (i <= mid) aux[k++] = a[i++]; // merge any remaining from left
        while (j <= hi)  aux[k++] = a[j++]; // ...or any remaining from right

        for (; lo != k; ++lo) a[lo] = aux[lo]; // copy back after merge
        return swaps;
    }

    private static long Mergesort(this int[] a, int[] aux, int lo, int hi)
    {
        if (lo >= hi) return 0;

        var mid = lo + (hi - lo) / 2;
        var swaps = a.Mergesort(aux, lo, mid) + a.Mergesort(aux, mid + 1, hi);
        return swaps + a.Merge(aux, lo, hi);
    }

    internal static long Mergesort(this int[] a) // returns number of swaps
        => a.Mergesort(new int[a.Length], 0, a.Length - 1);
}

internal static class Solution {
    private static void Main()
    {
        for (var d = int.Parse(Console.ReadLine()); d > 0; --d) {
            Console.ReadLine(); // don't need n
            var a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
            Console.WriteLine(a.Mergesort());
        }
    }
}
