using System;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Arith {
    internal static int[,] ComputeBinomialCoefficientsModulo(int size, int mod)
    {
        if (size < 2) size = 2;

        var c = new int[size, size];
        c[0, 0] = c[1, 0] = c[1, 1] = 1;

        for (var n = 2; n != size; ++n) {
            c[n, 0] = c[n, n] = 1;

            for (var r = 1; r != n; ++r)
                c[n, r] = (c[n - 1, r - 1] + c[n - 1, r]) % mod;
        }

        return c;
    }
}

internal static class Solution {
    private static int ReadValue() => int.Parse(Console.ReadLine());

    private static int[] ReadRecord()
            => Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

    private static int[][] ReadAllRecords()
            => Enumerable.Range(0, ReadValue())
                         .Select(i => ReadRecord())
                         .ToArray();

    private static void Main()
    {
        const int mod = 1000000007;

        var pairs = ReadAllRecords();
        var sums = Array.ConvertAll(pairs, nm => nm[0] + nm[1]);
        var c = Arith.ComputeBinomialCoefficientsModulo(sums.Max() + 1, mod);

        foreach (var i in Enumerable.Range(0, pairs.Length))
            Console.WriteLine(c[sums[i], pairs[i][0]]);
    }
}
