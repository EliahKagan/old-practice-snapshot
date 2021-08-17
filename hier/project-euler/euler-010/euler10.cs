// euler10.cs - Project Euler problem 10: Summation of primes

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

[Serializable] internal class UnreachableException : NotSupportedException { }

internal static class Prime {
    private enum Kind { Prime, Composite } // must appear in this order

    private static bool PrimeKind(Kind kind)
    {
        return kind == Kind.Prime;
    }

    private static Kind[] GetKindArray(int size)
    {
        Contract.Assert(size > 2);

        var a = new Kind[size];
        Contract.Assert(a.All(PrimeKind));

        a[1] = a[0] = Kind.Composite;
        return a;
    }

    private static Kind[] RawSieve(int size)
    {
        var a = GetKindArray(size);
        
        for (var i = 0; (i = Array.FindIndex(a, i + 1, PrimeKind)) != -1; ) {
            for (var j = i * 2; j < size; j += i)
                a[j] = Kind.Composite;
        }

        return a;
    }

    internal static IEnumerable<int> Sieve(int size)
    {
        var a = RawSieve(size);
        return Enumerable.Range(0, size).Where(i => PrimeKind(a[i]));
    }
}

internal static class Program {
    private static void Die(string format) // supply "{0}" for program name
    {
        Console.Error.WriteLine(format, Environment.GetCommandLineArgs()[0]);
        Environment.Exit(1);
    }

    private static int? Parse(string[] args)
    {
        Contract.Assert(args != null);

        if (!args.Any()) return null;

        try {
            if (args.Length == 1) return int.Parse(args[0]);
        }
        catch (FormatException) { }
        catch (OverflowException) { }

        Die("Usage:  {0} [upper-bound]");
        throw new UnreachableException();
    }

    private static void Main(string[] args)
    {
        try {
            var size = Parse(args) ?? 2000000;

            if (size <= 2)
                Console.WriteLine(0L);
            else
                Console.WriteLine(Prime.Sieve(size).Sum(i => (long)i));
        }
        catch (OverflowException) {
            Die("{0}: error: arithmetic overflow occurred");
        }
    }
}
