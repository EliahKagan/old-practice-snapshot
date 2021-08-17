<Query Kind="Program" />

internal static class Algo {
    private static int Merge(this int[] a, int[] aux, int lo, int hi)
    {
        var mid = lo + (hi - lo) / 2;

        var i = lo;
        var j = mid + 1;
        var k = lo;
        
        while (i <= mid && j <= hi) // merge from left and right sides
            aux[k++] = (a[i] <= a[j] ? a[i++] : a[j++]);
        
        var swaps = j - mid - 1;

        while (i <= mid) aux[k++] = a[i++]; // merge any remaining from left
        while (j <= hi)  aux[k++] = a[j++]; // ...or any remaining from right

        for (; lo != k; ++lo) a[lo] = aux[lo]; // copy back after merge
        return swaps;
    }

    private static int Mergesort(this int[] a, int[] aux, int lo, int hi)
    {
        if (lo >= hi) return 0;

        var mid = lo + (hi - lo) / 2;
        var swaps = a.Mergesort(aux, lo, mid) + a.Mergesort(aux, mid + 1, hi);
        return swaps + a.Merge(aux, lo, hi);
    }

    internal static int Mergesort(this int[] a) // returns number of swaps
        => a.Mergesort(new int[a.Length], 0, a.Length - 1);
}

internal static class UnitTest {
    private static void Main()
    {
        foreach (var a in new[] { new[] { 1, 2, 3 }, new[] { 2, 4, 1 },
                                  new[] { 1, 1, 1, 2, 2 }, new[] { 2, 1, 3, 1, 2 } })
            a.Mergesort().Dump();
    }
}
