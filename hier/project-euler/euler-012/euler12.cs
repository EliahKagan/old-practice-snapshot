// euler12.cs - Project Euler problem 12: Highly divisible triangular number

//#define DEBUG
#define FASTER_FACTORING

using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Security;

[assembly: System.Reflection.AssemblyVersion("0.1.0.1")]

[Serializable]
internal sealed class UnreachableException : NotSupportedException { }

internal static class Arith {
    private static IEnumerable<BigInteger> BigRange(BigInteger start,
                                                    BigInteger count)
    {
        if (count.Sign < 0) throw new ArgumentOutOfRangeException("count");

        for (; !count.IsZero; --count, ++start)
            yield return start;

        yield break;
    }

    internal static IEnumerable<BigInteger> GetFactors(BigInteger n)
    {
        Contract.Assert(n.Sign > 0);

#if !FASTER_FACTORING
        return from i in BigRange(BigInteger.One, n)
               where n % i == BigInteger.Zero
               select i;
#else
        var done = n / new BigInteger(2) + BigInteger.One;
        for (var i = BigInteger.One; i != done; ++i)
            if (n % i == BigInteger.Zero) yield return i;

        yield return n;
        yield break;
#endif
    }

    internal static IEnumerable<BigInteger> TriangularNumbers
    {
        get {
            var n = BigInteger.Zero;
            for (var i = BigInteger.One; ; ++i)
                yield return n += i;
        }
    }
}

internal static class ColorConsole {
    private static SystemException color_fail = null;
    
    internal static bool CanColor
    {
        get {
            return color_fail == null;
        }
    }

    internal static void WarnIfFailed()
    {
        if (!CanColor) {
            Console.Error.WriteLine("{0}: warning: bad output coloring: {1}",
                    Environment.GetCommandLineArgs()[0], color_fail.Message);
        }
    }

    internal static ConsoleColor Color
    {
        set {
            if (CanColor) {
                try {
                    Console.ForegroundColor = value;
                }
                catch (SystemException e) {
                    if (e is SecurityException || e is IOException)
                        color_fail = e;
                    else throw;
                }
            }
        }
    }
}

internal enum Mode { Run, Check }
internal enum Verbosity { Normal, Quiet }

internal static class Output {
    // Displays n, its factors, and its factor count. Returns the count.
    internal static BigInteger PrintWithFactors(BigInteger n)
    {
        Contract.Assert(n.Sign > 0);

        ColorConsole.Color = ConsoleColor.Yellow;
        Console.Write(" {0,6}", n);
        ColorConsole.Color = ConsoleColor.Gray;

        var sep = ": ";
        var count = BigInteger.Zero;

        foreach (var k in Arith.GetFactors(n)) {
            Console.Write("{0}{1}", sep, k);
            sep = ",";
            ++count;
        }

        Console.Write(" (");
        ColorConsole.Color = ConsoleColor.Cyan;
        Console.Write(count);
        ColorConsole.Color = ConsoleColor.Gray;
        Console.WriteLine(')');

        Contract.Assert(1 <= count && count <= n);
        return count;
    }

    // Emits one record per nums value, showing it, its factors, and its factor
    // count. But stops after showing a value with more than threshold factors.
    // When verbosity = Verbosity.Quiet, prints only that one final record.
    internal static void PrintWithFactors(IEnumerable<BigInteger> nums,
            BigInteger threshold, Verbosity verbosity = Verbosity.Normal)
    {
        switch (verbosity) {
        case Verbosity.Normal:
            foreach (var n in nums)
                if (PrintWithFactors(n) > threshold) break;

            break;

        case Verbosity.Quiet:
            foreach (var n in nums) {
                if (Arith.GetFactors(n).Count() > threshold) {
                    PrintWithFactors(n);
                    break;
                }
            }

            break;
        }

        ColorConsole.WarnIfFailed();
    }
}

internal static class ConfigurationEx {
    internal static Mode GetMode(this Tuple<Mode, BigInteger, Verbosity> self)
    {
        return self.Item1;
    }

    internal static BigInteger
    GetThreshold(this Tuple<Mode, BigInteger, Verbosity> self)
    {
        return self.Item2;
    }

    internal static Verbosity
    GetVerbosity(this Tuple<Mode, BigInteger, Verbosity> self)
    {
        return self.Item3;
    }
}

internal static class Program {
    private static Tuple<Mode, BigInteger, Verbosity>
    GetConfiguration(string[] args)
    {
        Contract.Assert(args != null);

        try {
            switch (args.Length) {
            case 0:     // run mode, default threshold
                return Tuple.Create(Mode.Run, new BigInteger(500),
                                              Verbosity.Quiet);

            case 1:     // run mode, custom threshold
                var n = BigInteger.Parse(args[0]);
                return Tuple.Create(Mode.Run, BigInteger.Abs(n),
                                    (n.Sign < 0 ? Verbosity.Quiet
                                                : Verbosity.Normal));

            case 2:     // check mode, custom "threshold" is only value checked
                if ((new[] { "-c", "--check" }).Contains(args[0].ToLower())) {
                    return Tuple.Create(Mode.Check, BigInteger.Parse(args[1]),
                                                    Verbosity.Quiet);
                }

                break;
            }
        }
        catch (FormatException) { }

        Console.Error.WriteLine("Usage:  {0} [--check|-c] [[-]divisor-number]",
                                Environment.GetCommandLineArgs()[0]);
        Environment.Exit(1);

        throw new UnreachableException();
    }

    private static void Main(string[] args)
    {
        var cfg = GetConfiguration(args); // mode, threshold, verbosity

        switch (cfg.GetMode()) {
        case Mode.Run:
            Output.PrintWithFactors(Arith.TriangularNumbers,
                                    cfg.GetThreshold(), cfg.GetVerbosity());
            break;

        case Mode.Check:    // For example:  euler12 -c 76576500
            Output.PrintWithFactors(cfg.GetThreshold());
            ColorConsole.WarnIfFailed();
            break;
        }
    }
}
