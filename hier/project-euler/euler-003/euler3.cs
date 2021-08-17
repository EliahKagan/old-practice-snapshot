// euler3.cs - Project Euler problem 3: Largest prime factor

using System;
using System.Diagnostics.Contracts;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

[Serializable] internal class UnreachableException : NotSupportedException { }

internal static class Program {
    private static void Die(string msg)
    {
        Contract.Assert(msg != null);

        Console.Error.WriteLine("{0}: error: {1}",
                                Environment.GetCommandLineArgs()[0], msg);
        Environment.Exit(1);
    }

    private static long Parse(string s)
    {
        Contract.Assert(s != null);

        try {
            var n = long.Parse(s);
            if (n < 2) Die("input must be at least 2");
            return n;
        }
        catch (FormatException) { Die("input not an integer"); }
        catch (OverflowException) { Die("input too big");  }

        throw new UnreachableException();
    }

    private static long Parse(string[] args)
    {
        Contract.Assert(args != null);

        if (args.Length > 1) Die("too many arguments");
        return args.Length == 0 ? 600851475143 : Parse(args[0]);
    }

    private static long MaxPrimeFactor(long n)
    {
        Contract.Assert(n > 1);

        var i = 1L;

        do {
            ++i;
            while (n % i == 0) n /= i;
        }
        while (n != 1);

        return i;
    }

    private static void Main(string[] args)
    {
        var n = Parse(args);

        Console.WriteLine("{0} is the largest prime factor of {1}.",
                          MaxPrimeFactor(n), n);
    }
}
