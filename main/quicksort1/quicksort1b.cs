using System;

internal static class Solution {
    private static void Partition(int[] a)
    {
        var left = new int[a.Length];
        var equal = new int[a.Length];
        var right = new int[a.Length];

        var i = 0;
        var j = 0;
        var k = 0;

        for (var h = 0; h != a.Length; ++h) {
            if (a[h] < a[0]) left[i++] = a[h];
            else if (a[h] == a[0]) equal[j++] = a[h];
            else right[k++] = a[h];
        }

        var hh = 0;
        for (; hh != i; ++hh) a[hh] = left[hh];
        for (var jj = 0; jj != j;) a[hh++] = equal[jj++];
        for (var kk = 0; kk != k;) a[hh++] = right[kk++];
    }

    private static void Main()
    {
        Console.ReadLine(); // don't need n
        var a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
        Partition(a);
        Console.WriteLine(string.Join(" ", a));
    }
}
