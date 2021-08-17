// euler12a.cs - Project Euler problem 12: Highly divisible triangular number
//               Speed-optimized version (the original version was too slow).
//
// To build with optimizations:  csc /debug- /optimize+ /checked- euler12a.cs

using System;
using System.Diagnostics.Contracts;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

[Serializable]
internal sealed class UnreachableException : NotSupportedException { }

internal static class Program {
    private static int? Parse(string[] args)
    {
        Contract.Assert(args != null);

        if (args.Length == 0) return null;

        try {
            if (args.Length == 1) {
                var n = int.Parse(args[0]);
                if (n > 0) return n;
            }
        }
        catch (FormatException) { }
        catch (OverflowException) { }

        Console.Error.WriteLine("Usage:  {0} [number-of-divisors]",
                                Environment.GetCommandLineArgs()[0]);
        Environment.Exit(1);

        throw new UnreachableException();
    }

    private static void GiveResult(long result, long factors)
    {
        Console.WriteLine("{0} has {1} divisors.", result, factors);
        Environment.Exit(0);
    }

    private static void Main(string[] args)
    {
        long threshold = Parse(args) ?? 500;

        for (long n = 0, i = 1; ; ++i) {
            n += i; // n is the ith triangular number

            long factors = 1; // one, for n itself (not covered below)
            for (long over_half = n / 2 + 1, k = 1; k != over_half; ++k)
                if (n % k == 0) ++factors;

            if (factors > threshold) GiveResult(n, factors);
        }
    }
}
