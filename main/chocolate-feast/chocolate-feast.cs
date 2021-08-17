using System;
using System.Linq;

internal static class Solution {
    private static int ComputeTotalUnitsPurchased(int n, int c, int m)
    {
        var u = n / c;  // total units of chocolate purchased so far
        var w = u;      // current number of wrappers held
        int du;         // units acquired in an individual purchase

        while ((du = Math.DivRem(w, m, out w)) != 0) {
            u += du;
            w += du;
        }

        return u;
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, int.Parse(Console.ReadLine()))) {
            var a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
            Console.WriteLine(ComputeTotalUnitsPurchased(a[0], a[1], a[2]));
        }
    }
}
