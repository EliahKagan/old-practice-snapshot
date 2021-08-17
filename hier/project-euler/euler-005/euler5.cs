// euler5.cs - Project Euler problem 5: Smallest multiple

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
        return args.Length == 0 ? 20 : Parse(args[0]);
    }

    private static void Main(string[] args)
    {
        var factors = Enumerable.Range(1, Parse(args));
        var n = 1;
        while (factors.Any(i => n % i != 0)) ++n;
        Console.WriteLine(n);
    }
}
