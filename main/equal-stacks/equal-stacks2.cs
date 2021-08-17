using System;
using System.Collections.Generic; // for Comparer<T>.Create(Comparison<T>)

[assembly: System.Reflection.AssemblyVersion("1.1.0.0")]

internal static class ArrayEx {
    internal static bool TrueForRest<T>(this T[] a, Predicate<T> f)
    {
        for (var i = 1; i < a.Length; ++i)
            if (!f(a[i])) return false;

        return true;
    }
}

internal static class Solution {
    private static int[] GetRecord()
            => Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

    private static void BackwardsRunningSumInPlace(int[][] hs, int[] ns)
    {
        for (var i = 0; i != ns.Length; ++i)
            while (--ns[i] > 0) hs[i][ns[i] - 1] += hs[i][ns[i]];
    }

    private static int FindMaxLevelHeight(int[][] hs)
    {
        var gt_comp = Comparer<int>.Create((m, n) => n.CompareTo(m));

        foreach (var top in hs[0]) {
            if (hs.TrueForRest(h => Array.BinarySearch(h, top, gt_comp) >= 0))
                return top;
        }

        return 0;
    }

    private static void Main()
    {
        var ns = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        var hs = Array.ConvertAll(ns, n => GetRecord());
        BackwardsRunningSumInPlace(hs, ns);
        Console.WriteLine(FindMaxLevelHeight(hs));
    }
}
