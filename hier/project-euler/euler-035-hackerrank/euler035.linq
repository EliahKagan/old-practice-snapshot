<Query Kind="Program" />

internal static class Arith {
    internal static IEnumerable<int> Sieve(int n) // yields primes up to n
    {
        var a = new bool[n + 1]; // false means not marked as composite
    
        var imax = Convert.ToInt32(Math.Floor(Math.Sqrt(n)));
        for (var i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                var jstep = i * 2;
                for (var j = i * i; j <= n; j += jstep) a[j] = true;
            }
        }
    
        yield return 2;
        for (var k = 3; k <= n; k += 2)
            if (!a[k]) yield return k;
    }
}

internal static class CircularPrimes {
    private const int Base = 10;

    internal const int DefaultN = 1000000;
    
    private static IEnumerable<int> ToDigits(this int k)
    {
        do yield return k % Base;
        while ((k /= Base) != 0);
    }

    private static IEnumerable<int> Rotations(int val)
    {
        var digits = val.ToDigits().ToArray();
        if (digits.Contains(0)) yield break;
        yield return val;
        
        var len = digits.Length;
        for (var i = 1; i != len; ++i) {
            var ret = digits[i];
            var mul = 1;
            for (var j = i; ++j != len; ) ret += digits[j] * (mul *= Base);
            ret += digits[0] * (mul *= Base);
            for (var j = 0; ++j != i; ) ret += digits[j] * (mul *= Base);
            yield return ret;
        }
    }
    
    private static int MinRotation(int val)
            => Rotations(val).DefaultIfEmpty(-1).Min();

    // Enumerates circular primes below n. Requires n = 10**p for some p > 0.
    internal static IOrderedEnumerable<int> Compute(int n)
            => Arith.Sieve(n).GroupBy(MinRotation)
                             .Where(g => g.Count() == Rotations(g.Key).Distinct().Count())
                             .SelectMany(g => g)
                             .OrderBy(p => p);
    internal static IOrderedEnumerable<int> Compute() => Compute(DefaultN);
}

internal static class UnitTest {
    private static void Main()
    {
        CircularPrimes.Compute().Dump();
    }
}