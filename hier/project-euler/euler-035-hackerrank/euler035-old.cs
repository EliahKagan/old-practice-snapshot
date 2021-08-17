using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Arith {
    private static IEnumerable<int> Sieve(int n) // yields primes up to n
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

    internal static int[] Primes(int n) => Sieve(n).ToArray(); // primes to n
}

internal static class CircularPrimes {
    private const int Base = 10;

    internal const int DefaultN = 1000000;
    
    private static IEnumerable<int> ToDigits(this int k)
    {
        do yield return k % Base;
        while ((k /= Base) != 0);
    }

    private static IEnumerable<int> Rotations(int val) // not including val
    {
        var digits = val.ToDigits().ToArray();
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

    private static IEnumerable<int> EmitFrom(int[] primes)
    {
        var n = primes.Length;
        var emit = new bool?[n];

        var i = 0;
        for (; primes[i] <= 11; ++i) emit[i] = true;

        for (; i != n; ++i) {
            if (emit[i].HasValue) continue;

            //var r = Rotations(primes[i]).OrderBy(p => p).Distinct().ToArray();

            var p = primes[i];
            var start = i + 1;
            var length = n - start;

            var r = Rotations(p)
                    .TakeWhile(k => p < k)
                    .Select(k => Array.BinarySearch(primes, start, length, k))
                    .TakeWhile(j => j >= 0)
                    .ToArray();



            //if (r.Length == 0 || r[0] < primes[i]) {
            //    emit[i] = false;
            //    continue;
            //}
        }
    }

    internal static int[] Compute(int n) // needs n = 10**p, where p > 0
            => EmitFrom(Arith.Primes(n)).ToArray();

    internal static int[] Compute() => Compute(DefaultN);
}

internal static class Solution {

}