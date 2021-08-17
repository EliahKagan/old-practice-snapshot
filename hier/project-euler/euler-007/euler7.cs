// euler7.cs - Project Euler problem 7: 10001st prime

using System;
using System.Diagnostics.Contracts;
using System.Linq;

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

    private static int Parse(string s)
    {
        Contract.Assert(s != null);

        try {
            var n = int.Parse(s);
            if (n < 1) Die("input must be (strictly) positive");
            return n;
        }
        catch (FormatException) { Die("input not an integer"); }
        catch (OverflowException) { Die("input too big"); }

        throw new UnreachableException();
    }

    private static int Parse(string[] args)
    {
        Contract.Assert(args != null);

        if (args.Length > 1) Die("too many arguments");
        return args.Length == 0 ? 10001 : Parse(args[0]);
    }

    private static int[] GetPrimes(int n)
    {
        Contract.Assert(n > 0);

        var seq = new int[n];
        seq[0] = 2;

        for (var i = 1; i != n; ++i) {
            var p = seq[i - 1] + 1;
            while (Enumerable.Range(0, i).Any(j => p % seq[j] == 0)) ++p;
            seq[i] = p;
        }

        return seq;
    }

    private static void Main(string[] args)
    {
        try {
            Console.WriteLine(GetPrimes(Parse(args)).Last());
        }
        catch (OutOfMemoryException) { Die("out of memory"); }
    }
}
