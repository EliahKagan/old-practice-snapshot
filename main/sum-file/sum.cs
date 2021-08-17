// sum.cs - reads and sums integers, one per line, from a file
// To build:   csc /r:System.Numerics.dll sum.cs   (or "mcs ...")

using System;
using System.Diagnostics.Contracts;
using System.IO;
using System.Numerics;
using System.Security;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

[Serializable] internal class UnreachableException : NotSupportedException { }

internal static class Program {
    private static void Die(string format, params object[] args)
    {
        Contract.Assert(format != null && args != null);

        Console.Error.WriteLine("{0}: error: {1}",
                                Environment.GetCommandLineArgs()[0],
                                string.Format(format, args));
        Environment.Exit(1);
    }

    private static BigInteger Parse(string s)
    {
        Contract.Assert(s != null);

        try {
            return BigInteger.Parse(s);
        }
        catch (FormatException) {
            Die("got non-number \"{0}\"", s);
        }

        throw new UnreachableException();
    }

    private static BigInteger Sum(string path)
    {
        Contract.Assert(path != null);

        var n = BigInteger.Zero;

        try {
            foreach (var s in File.ReadLines(path)) n += Parse(s);
        }
        catch (ArgumentException) {
            Die("{0}: invalid path", path);
        }
        catch (SystemException e) {
            if (e is IOException || e is SecurityException
                                 || e is UnauthorizedAccessException)
                Die("{0}: {1}", path, e.Message);

            throw;
        }

        return n;
    }

    private static void Main(string[] args)
    {
        if (args.Length > 1) Die("too many arguments");

        try {
            Console.WriteLine(Sum(args[0]));
        }
        catch (IndexOutOfRangeException) {
            Die("too few arguments (need input filename)");
        }
        catch (OutOfMemoryException) {
            Die("out of memory");
        }
    }
}
