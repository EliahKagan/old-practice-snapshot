// euler9.cs - Project Euler problem 9: Special Pythagorean triplet

using System;
using System.Diagnostics.Contracts;
using System.Linq;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

[Serializable] internal class UnreachableException : NotSupportedException { }

internal static class Int32Ex {
    internal static int Sq(this int self)
    {
        return checked(self * self);
    }
}

internal static class Program {
    // This is a very inefficient algorithm... but it's also very simple,
    // only needs to run once, and modern computers are quite fast.
    private static Tuple<int, int, int> GetSpecialTriple()
    {
        var max = 1000; // any sufficiently high number will do

        checked {
            foreach (var b in Enumerable.Range(1, max)) {
                foreach (var a in Enumerable.Range(1, b - 1)) {
                    var c_squared = a.Sq() + b.Sq();
                    var c = (int)Math.Sqrt(c_squared);

                    if (c.Sq() == c_squared && a + b + c == 1000)
                        return Tuple.Create(a, b, c);
                }
            }
        }

        Console.Error.WriteLine("{0}: error: failed to find special triplet",
                                Environment.GetCommandLineArgs()[0]);
        Environment.Exit(1);
        throw new UnreachableException();
    }

    private static void Main()
    {
        var triple = GetSpecialTriple();
        Contract.Assert(checked(triple.Item1.Sq() + triple.Item2.Sq()
                                    == triple.Item3.Sq()));

        Console.WriteLine("{0}^2 + {1}^2 = {2}^2.",
                          triple.Item1, triple.Item2, triple.Item3);

        Console.WriteLine("{0} + {1} + {2} = {3}.",
                          triple.Item1, triple.Item2, triple.Item3,
                          triple.Item1 + triple.Item2 + triple.Item3);

        Console.WriteLine("({0})({1})({2}) = {3}.",
                          triple.Item1, triple.Item2, triple.Item3,
                          triple.Item1 * triple.Item2 * triple.Item3);
    }
}
