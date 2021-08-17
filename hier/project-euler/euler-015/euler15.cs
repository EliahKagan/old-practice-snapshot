// euler15.cs - Project Euler problem 15: Lattice paths
//
// For an n by n grid, each allowed path consists of n moves right and n moves
// down; only the order varies. First consider the related but different
// scenario wherein each move right is colored distinctly from n colors (while
// moves down remain uncolored, i.e., not distinguishable from each other).
// Given the step in which each move right takes place and its color (i.e., the
// function [color => step number]), the moves down are uniquely determined and
// thus may be disregarded. So this is the problem of placing n distinct
// objects in 2n positions and the number of possibilities is: (2n)! / n!
//
// The given problem differs in that the moves right aren't colored either. So
// the above solution is too great by a factor of the number of possible right
// move colorings (n!), and the solution here is: (2n)! / (n!)^2

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Numerics;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

internal static class BigIntegerEx {
    internal static IEnumerable<BigInteger> Range(BigInteger start,
                                                  BigInteger count)
    {
        Contract.Assert(count.Sign >= 0);

        for (; !count.IsZero; --count, ++start)
            yield return start;

        yield break;
    }

    internal static BigInteger Squared(this BigInteger n)
    {
        return n * n;
    }

    internal static BigInteger Factorial(this BigInteger n)
    {
        Contract.Assert(n.Sign >= 0);

        return Range(BigInteger.One, n)
                .Aggregate(BigInteger.One, BigInteger.Multiply);
    }
}

internal static class Program {
    private static void PrintPathCount(BigInteger n)
    {
        if (n.Sign < 0) throw new ArgumentOutOfRangeException("n", n, "n < 0");

        Console.WriteLine("{0,6} :  {1}", n,
                          (n * 2).Factorial() / n.Factorial().Squared());
    }

    private static void Error(string format, params object[] args)
    {
        Contract.Assert(format != null && args != null);

        Console.Error.WriteLine("{0}: error: {1}",
                                Environment.GetCommandLineArgs()[0],
                                string.Format(format, args));
        Environment.ExitCode = 1;
    }

    private static void Main(string[] args)
    {
        if (!args.Any()) {
            foreach (var n in BigIntegerEx.Range(BigInteger.One, 20))
                PrintPathCount(n);

            return;
        }

        foreach (var arg in args) {
            try {
                PrintPathCount(BigInteger.Parse(arg));
            }
            catch (FormatException) {
                Error("\"{0}\" is not a number", arg.Trim());
            }
            catch (ArgumentOutOfRangeException e) {
                Error("{0} is negative", e.ActualValue);
            }
        }
    }
}
