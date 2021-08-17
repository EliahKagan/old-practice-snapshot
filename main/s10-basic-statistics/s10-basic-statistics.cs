using System;
using System.Linq;
using System.Collections.Generic;

internal static class Solution {
    private static double Mean(int[] a) => (double)a.Sum() / a.Length;

    private static double Median(int[] a) // assumes a is sorted
    {
        var i = a.Length / 2;
        var x = (double)a[i - 1];
        return a.Length % 2 == 0 ? (x + a[i]) / 2.0 : x;
    }

    private static int Mode(int[] a) // assumes a is sorted
    {
        var mode = 0;
        var freq = 0;

        var i = 0;
        do {
            var j = Array.FindIndex(a, i, e => a[i] < e);
            if (j == -1) j = a.Length;

            var d = j - i;
            if (freq < d || (freq == d && a[i] < mode)) {
                mode = a[i];
                freq = d;
            }

            i = j;
        }
        while (i < a.Length);

        return mode;
    }

    private static void Print(double x) => Console.WriteLine("{0:F1}", x);

    private static void Main()
    {
        Console.ReadLine(); // don't need n
        var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Array.Sort(a);

        Print(Mean(a));
        Print(Median(a));
        Console.WriteLine(Mode(a));
    }
}
