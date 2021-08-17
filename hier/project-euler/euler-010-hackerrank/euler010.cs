using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class ListEx { // some algorithm extension methods on List<>
    private static int FindMaxLessOrEqual(this List<long> seq, long key,
                                          int from, int to)
    {
        if (to < from) return to;

        var i = from + (to - from) / 2;

        if (key < seq[i]) return FindMaxLessOrEqual(seq, key, from, i - 1);
        if (key > seq[i]) return FindMaxLessOrEqual(seq, key, i + 1, to);
        return i;
    }

    // Returns the index of the last element of a not greater than n.
    // Assumes a is strictly increasing and contains such an element.
    internal static int FindMaxLessOrEqual(this List<long> seq, long key)
            => FindMaxLessOrEqual(seq, key, 0, seq.Count - 1);

    internal static List<long> RunningSum(this List<long> seq)
    {
        var sums = new List<long>(seq.Count);

        var acc = 0L;
        foreach (var elem in seq) sums.Add(acc += elem);

        return sums;
    }
}

internal static class Arith { // number-theoretic methods
    private static IEnumerable<long> Sieve(int n) // yields primes up to n
    {
        var a = new bool[n + 1]; // false means not marked as composite
    
        var imax = Convert.ToInt32(Math.Floor(Math.Sqrt(n)));
        for (var i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                var jstep = i * 2;
                for (var j = i * i; j <= n; j += jstep) a[j] = true;
            }
        }
    
        yield return 2L;
        for (var k = 3; k <= n; k += 2)
            if (!a[k]) yield return k; // int-to-long conversion happens here
    }

    internal static List<long> Primes(int n) // yields primes to n, as List<>
            => Sieve(n).ToList();
}

internal static class Solution {
    private static List<long> ReadUpperBounds()
    {
        var t = int.Parse(Console.ReadLine());
        var a = new List<long>(t);
        while (t-- > 0) a.Add(long.Parse(Console.ReadLine()));
        return a;
    }

    private static void Main()
    {
        var bounds = ReadUpperBounds();
        var primes = Arith.Primes((int)bounds.Max());
        var sums = primes.RunningSum();

        foreach (var n in bounds)
            Console.WriteLine(sums[primes.FindMaxLessOrEqual(n)]);
    }
}
