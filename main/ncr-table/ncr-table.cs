using System;
using System.Collections.Generic;
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

    internal static void PrintBinomialCoefficientRow(int[,] c, int n)
    {
        for (var r = 0; r != n; ++r) Console.Write("{0} ", c[n, r]);
        Console.WriteLine(c[n, n]);
    }
}

internal static class Solution {
    private static int ReadValue() => int.Parse(Console.ReadLine());

    private static IEnumerable<int> ReadAllValues()
            => from i in Enumerable.Range(0, ReadValue()) select ReadValue();

    private static void Main()
    {
        const int mod = 1000000000;

        var ns = ReadAllValues().ToList();
        var c = Arith.ComputeBinomialCoefficientsModulo(ns.Max() + 1, mod);

        ns.ForEach(n => Arith.PrintBinomialCoefficientRow(c, n));
    }
}