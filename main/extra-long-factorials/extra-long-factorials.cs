using System;
using System.Diagnostics.Contracts;
using System.Numerics;

internal static class Solution {
    private static BigInteger Factorial(BigInteger n)
    {
        Contract.Assert(n.Sign > 0);

        var p = BigInteger.One;
        for (; n != BigInteger.One; --n) p *= n;
        return p;
    }

    private static void Main()
    {
        Console.WriteLine(Factorial(BigInteger.Parse(Console.ReadLine())));
    }
}
