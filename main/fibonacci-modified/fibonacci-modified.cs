#define DEBUG

using System;
using System.Diagnostics.Contracts;
using System.Numerics;

internal static class Solution {
    private static BigInteger FibModified(BigInteger a, BigInteger b, int n)
    {
        Contract.Assert(n > 2);

        for (var i = 2; i != n; ++i) {
            var tmp = a;
            a = b;
            b = b * b + tmp;
        }

        return b;
    }

    private static void Main()
    {
        var input = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
        Console.WriteLine(FibModified(input[0], input[1], input[2]));
    }
}
