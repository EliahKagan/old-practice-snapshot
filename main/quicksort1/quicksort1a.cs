using System;
using System.Linq; // used only for printing

internal static class Solution {
    private static void Partition(int[] a)
    {
        var n = a.Length;

        var lt = new int[n - 1];
        var gt = new int[n - 1];
        var eq = new int[n];

        var ltn = 0;
        var gtn = 0;
        var eqn = 1;

        var p = eq[0] = a[0];

        for (var i = 1; i < n; ++i) {
            if (a[i] < p)       lt[ltn++] = a[i];
            else if (a[i] > p)  gt[gtn++] = a[i];
            else                eq[eqn++] = a[i];
        }

        var b = lt.Take(ltn).Concat(eq.Take(eqn)).Concat(gt.Take(gtn));
        Console.WriteLine(string.Join(" ", b));
    }

    private static void Main()
    {
        Console.ReadLine();
        Partition(Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse));
    }
}
