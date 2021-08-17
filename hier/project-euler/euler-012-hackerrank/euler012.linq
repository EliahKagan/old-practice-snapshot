<Query Kind="Program">
  <Namespace>static System.Diagnostics.Contracts.Contract</Namespace>
</Query>

internal static class Util {
    internal static void Swap<T>(ref T a, ref T b)
    {
        var tmp = a;
        a = b;
        b = tmp;
    }
}

internal static class Int32Ex {
    // Casting from double extracts square roots accurately from small ints.
    internal static int Sqrt(this int n) => (int)Math.Sqrt(n);
}

internal static class Primes {
    private static IEnumerable<int> Sieve(int n) // yields primes up to n
    {
        var a = new bool[n + 1]; // false means not marked as composite

        var imax = n.Sqrt();
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

    internal static int[] To(int n) => Sieve(n).ToArray(); // all primes <= n

    // Helper method for Factorize(). Factorizes n, assuming that it is odd.
    private static void FactorizeOdd(this int[] primes,
                                     int[] factorization, int n)
    {
        var len = primes.Length;

        var i = 1;
        for (var sqrt = n.Sqrt(); i != len && primes[i] <= sqrt; ++i) {
            if (n % primes[i] == 0) {
                do {
                    ++factorization[i];
                    n /= primes[i];
                }
                while (n % primes[i] == 0);

                if (n == 1) return;
            }
        }
        
        // what remains (since n != 1 here) is a single prime factor > sqrt
        ++factorization[Array.BinarySearch(primes, i, len - i, n)];
    }

    // Increments factorization[i] for each factor of primes[i] in n (n > 0).
    // primes must the first primes.length prime numbers, sorted increasingly.
    internal static void Factorize(this int[] primes,
                                   int[] factorization, int n)
    {
        //var orig = n;
        
        while ((n & 1) == 0) { // quickly pull out all factors of 2
            n >>= 1;
            ++factorization[0];
        }

        if (n != 1) primes.FactorizeOdd(factorization, n);
        
        //primes.Zip(factorization.Reverse().SkipWhile(i => i == 0).Reverse(),
        //           (Prime, Exponent) => new { Prime, Exponent })
        //      .Dump($"Prime factorization of {orig}:");
    }
}

internal static class PrimesEx { // more methods, useful for triangular numbers
    private static int CountProductDivisors(int len, int[] a, int[] b)
            => Enumerable.Range(0, len)
                         .Aggregate(1, (p, i) => p * (a[i] + b[i] + 1));

    internal static int CountFirstProductDivisors(this int[] primes,
            out int[] a, out int[] b, int k, Func<int, int> f)
    {
        var len = primes.Length;

        a = new int[len];
        primes.Factorize(a, f(k));

        b = new int[len];
        primes.Factorize(b, f(k + 1));

        return CountProductDivisors(len, a, b);
    }

    internal static int CountNextProductDivisors(this int[] primes,
            ref int[] a, ref int[] b, ref int k, Func<int, int> f)
    {
        Util.Swap(ref a, ref b);

        var len = primes.Length;

        Array.Clear(b, 0, len);
        primes.Factorize(b, f(++k + 1));

        return CountProductDivisors(len, a, b);
    }
}

internal static class TriangularNumbers {
    // Divide k by a single factor of 2, if it is divisible by 2.
    private static int Extract2(int k) => k % 2 == 0 ? k / 2 : k;

    // For sorted ns, the FindMinsWithDivisorCounts.ElementAt(i)th triangular
    // number is the smallest with >= ns[i] distinct integer divisors.
    private static IEnumerable<int> FindMinsWithDivisorCounts(int[] ns,
                                                              int kmax)
    {
        var primes = Primes.To(kmax + 1); // to factor max value of (k + 1)

        int[] a, b;
        var k = 1;
        var count = primes.CountFirstProductDivisors(out a, out b,
                                                     k, Extract2);

        foreach (var n in ns) {
            while (count <= n) {
                count = primes.CountNextProductDivisors(ref a, ref b,
                                                        ref k, Extract2);
            }

            yield return k;
        }
    }

    // For sorted ns, GetMinsWithDivisorCounts(ns)[i] is the smallest
    // triangular number with >= ns[i] distinct integer divisors.
    // Triangular numbers up to the (kmax)th one are considered; if the caller
    // doesn't pass sufficiently large kmax, an exception may be thrown.
    internal static int[] GetMinsWithDivisorCounts(int[] ns, int kmax)
            => FindMinsWithDivisorCounts(ns, kmax).Select(k => k * (k + 1) / 2)
                                                  .ToArray();
}

internal static class Solution {
    private static int Get() => int.Parse(Console.ReadLine());

    private static void Main()
    {
        const int kmax = 50000; // max count of triangular numbers to consider

        var range = Enumerable.Range(0, Get());
        var ns = range.Select(i => Get()).ToArray();
        var indices = range.ToArray();

        Array.Sort(ns, indices);
        var ans = TriangularNumbers.GetMinsWithDivisorCounts(ns, kmax);
        Array.Sort(indices, ans);

        foreach (var val in ans) Console.WriteLine(val);
    }
}
