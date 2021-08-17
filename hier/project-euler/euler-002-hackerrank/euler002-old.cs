using System.Collections.Generic;
using System.Linq;
using static System.Console;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class EnumerableEx {
    internal static IEnumerable<long> RunningSum(this IEnumerable<long> self)
    {
        var acc = 0L;
        foreach (var elem in self) yield return acc += elem;
    }
}

internal static class Arith {
    private static IEnumerable<long> EvenFib(long n) // Fibonacci seq. up to n
    {
        var a = 0L;
        var b = 2L;

        yield return a;
        do {
            yield return b;

            var tmp = a;
            a = b;
            b = tmp + b * 4;
        }
        while (b <= n);
    }

    internal static IEnumerable<long> EvenFibSums(long n) // even Fibo. up to n
            => EvenFib(n).RunningSum();
}

internal static class Solution {
    private static List<long> ReadUpperBounds()
    {
        var t = int.Parse(ReadLine());
        var a = new List<long>(t);
        while (t-- > 0) a.Add(long.Parse(ReadLine()));
        return a;
    }

    private static void Main()
    {
        var a = ReadUpperBounds();
        var m = a.Max();
        
    }
}
