using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Arith {
    internal static List<BigInteger> Factorials(this int n)
    {
        var seq = new List<BigInteger>(n + 1);
        seq.Add(BigInteger.One);

        var j = BigInteger.One;
        for (var i = 0; i != n; ++i, ++j) seq.Add(seq[i] * j);

        return seq;
    }

    private static int DigitSum(BigInteger n)
            => n.ToString("R").Sum(c => c - '0');

    internal static int[] DigitSumTable(this List<BigInteger> seq,
                                        IEnumerable<int> indices)
    {
        var table = new int[seq.Count]; // we rely on seq containing no zeros

        foreach (var n in indices)
            if (table[n] == 0) table[n] = DigitSum(seq[n]);

        return table;
    }
}

internal static class Solution {
    private static int ReadValue() => int.Parse(Console.ReadLine());

    private static List<int> ReadAllValues()
    {
        var t = ReadValue();
        var a = new List<int>(t);
        while (t-- > 0) a.Add(ReadValue());
        return a;
    }

    private static void Main()
    {
        var values = ReadAllValues();
        var table = values.Max().Factorials().DigitSumTable(values);

        values.ForEach(n => Console.WriteLine(table[n]));
    }
}
