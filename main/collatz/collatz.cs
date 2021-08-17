// collatz.cs - Collaz sequence generator

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

[assembly:System.Reflection.AssemblyVersion("0.1.0.1")]

[Serializable]
internal sealed class UnreachableException : NotSupportedException { }

internal static class Program {
    private static IEnumerable<long> Collatz(long n)
    {
        Contract.Assert(n > 0);

        for (; ; ) {
            yield return n;
            if (n == 1) yield break;
            n = (n % 2 == 0 ? n / 2 : checked(n * 3 + 1));
        }
    }

    private static long Parse(string[] args)
    {
        Contract.Assert(args != null);

        try {
            if (args.Length == 1) {
                var n = long.Parse(args[0]);
                if (n > 0) return n;
            }
        }
        catch (FormatException) { }
        catch (OverflowException) { }

        Console.Error.WriteLine("Usage:  {0} [start-value]",
                                Environment.GetCommandLineArgs()[0]);
        Environment.Exit(1);

        throw new UnreachableException();
    }

    private static void Main(string[] args)
    {
        var start = Parse(args);

        var sep = string.Empty;
        foreach (var val in Collatz(start)) {
            Console.Write("{0}{1}", sep, val);
            sep = ",";
        }

        Console.WriteLine(" ({0})", Collatz(start).Count());
    }
}