// euler16.cs - Project Euler problem 16: Power digit sum

using System;
using System.Diagnostics.Contracts;
using System.Globalization;
using System.Linq;
using System.Numerics;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

[Serializable]
internal sealed class UnreachableException : NotSupportedException { }

internal static class StringEx {
    internal static int Sum(this string self)
    {
        Contract.Assert(self != null);

        return Enumerable.Range(0, self.Length)
                         .Select(i => self.Substring(i, 1))
                         .Sum(d => int.Parse(d, CultureInfo.InvariantCulture));
    }
}

internal static class Program {
    private static int? Parse(string[] args)
    {
        Contract.Assert(args != null);

        if (!args.Any()) return null;

        try {
            if (args.Length == 1) {
                var n = int.Parse(args[0]);
                if (n >= 0) return n;
            }
        }
        catch (FormatException) { }
        catch (OverflowException) { }

        Console.Error.WriteLine("Usage:  {0} [exponent]",
                                Environment.GetCommandLineArgs()[0]);
        Environment.Exit(1);

        throw new UnreachableException();
    }

    private static void Main(string[] args)
    {
        var n = 2;
        var p = Parse(args) ?? 1000;

        var s = BigInteger.Pow(n, p)
                          .ToString("R", CultureInfo.InvariantCulture);

        Console.WriteLine("{0}^{1} = {2}{3}", n, p, s, Environment.NewLine);
        Console.WriteLine("Digits sum to {0}.", s.Sum());
    }
}
