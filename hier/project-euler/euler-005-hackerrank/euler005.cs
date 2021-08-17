using System.Collections.Generic;
using System.Linq;
using static System.Console;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Arith {
    private static long GreatestCommonDivisor(long m, long n)
            => n == 0L ? m : GreatestCommonDivisor(n, m % n);

    private static long LeastCommonMultiple(long m, long n)
            => m / GreatestCommonDivisor(m, n) * n;

    internal static List<long> LeastCommonMultiples(this IEnumerable<long> seq)
    {
        var lcm = seq.First();
        var a = new List<long> { lcm };

        foreach (var elem in seq.Skip(1))
            a.Add(lcm = LeastCommonMultiple(lcm, elem));

        return a;
    }
}

internal static class Solution {
    private static IEnumerable<long> Range(long start, long count)
    {
        while (count-- > 0L) yield return start++;
    }

    private static List<long> ReadUpperBounds()
    {
        var t = int.Parse(ReadLine());
        var a = new List<long>(t);
        while (t-- > 0) a.Add(long.Parse(ReadLine()));
        return a;
    }

    private static void Main()
    {
        var bounds = ReadUpperBounds();
        var lcms = Range(1L, bounds.Max()).LeastCommonMultiples();

        bounds.ForEach(n => WriteLine(lcms[(int)n - 1]));
    }
}
