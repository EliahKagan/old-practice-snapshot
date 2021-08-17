// euler2.cs - Project Euler problem 2: Even Fibonacci numbers

using System;
using System.Collections.Generic;

[assembly:System.Reflection.AssemblyVersion("0.1.0.0")]

[Serializable] internal class UnreachableException : NotSupportedException { }

internal static class Program {
    private static IEnumerable<int> Fib(int a, int b)
    {
        for (; ; ) {
            yield return b;

            var tmp = a;
            a = b;
            b += tmp;
        }
    }

    private static int SumEvens(int max)
    {
        var n = 0;

        foreach (var k in Fib(1, 2)) {
            if (k > max) return n;

            if (k % 2 == 0) {
                n += k;
#if DEBUG
                Console.WriteLine("{0} ({1})", k, n);
#endif
            }
        }

        throw new UnreachableException();
    }

    private static void Main()
    {
        Console.WriteLine(SumEvens(4000000));
    }
}
