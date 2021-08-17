// euler6.cs - Project Euler problem 6: Sum square difference

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
        return args.Length == 0 ? 100 : Parse(args[0]);
    }

    private static int Square(int n)
    {
        return n * n;
    }

    private static int SumSquareDifference(int max)
    {
        Contract.Assert(max > 0);

        var seq = Enumerable.Range(1, max);
        return Square(seq.Sum()) - seq.Select(Square).Sum();
    }

    private static void Main(string[] args)
    {
        Console.WriteLine(SumSquareDifference(Parse(args)));
    }
}
