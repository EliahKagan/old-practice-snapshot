// euler14.cs - Project Euler problem 14: Longest Collatz sequence
// To compile:  csc /debug- /optimize+ euler14.cs

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

[Serializable]
internal sealed class UnreachableException : NotSupportedException { }

internal static class Seq {
    // returns the Collatz sequence starting with k
    internal static IEnumerable<long> Collatz(long n)
    {
        Contract.Assert(n > 0);

        for (; ; ) {
            yield return n;
            if (n == 1) yield break;
            n = (n % 2 == 0 ? n / 2 : checked(n * 3 + 1));
        }
    }

    // returns values in [1, n) whose Collatz sequence(s) are of the greatest
    // length of any Collatz sequence that starts with a number in [1, n)
    internal static IEnumerable<long> FindLongestCollatz(long stop_before,
                                                         out int max_length)
    {
        Contract.Assert(stop_before > 0);

        max_length = 1;
        var a = new List<long>();

        for (long n = 1; n != stop_before; ++n) {
            var len = Collatz(n).Count();
            
            if (len < max_length) continue;

            if (len != max_length) {
                a.Clear();
                max_length = len;
            }

            a.Add(n);
        }

        return a;
    }
}

internal static class Program {
    private static void Die(string format) // supply "{0}" for program name
    {
        Console.Error.WriteLine(format, Environment.GetCommandLineArgs()[0]);
        Environment.Exit(1);
    }

    private static long? Parse(string[] args)
    {
        Contract.Assert(args != null);

        if (!args.Any()) return null;

        try {
            if (args.Length == 1) {
                var n = long.Parse(args[0]);
                if (n > 1) return n;
            }
        }
        catch (FormatException) { }
        catch (OverflowException) { }

        Die("Usage:  {0} [stop-before]");
        throw new UnreachableException();
    }

    private static void Main(string[] args)
    {
        var stop_before = Parse(args) ?? 1000000;

        try {
            int len;
            foreach (var n in Seq.FindLongestCollatz(stop_before, out len)) {
                Console.WriteLine("The Collatz chain from {0} has length {1}.",
                                  n, len);
            }
        }
        catch (OverflowException) {
            Die("{0}: error: arithmetic overflow while calculating sequence");
        }
    }
}
