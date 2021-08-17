<Query Kind="Program" />

internal static class Int32Ex {
    // Casting from double extracts square roots accurately from small ints.
    internal static int Sqrt(this int n) => (int)Math.Sqrt(n);
}

internal static class Combinatorics {
    internal static bool Advance(int len, int[] cycles, int[] orders)
    {
        var i = 0;
        while (i != len && cycles[i] == orders[i]) ++i;
        if (i == len) return false;

        for (var j = 0; j != i; ++j) cycles[j] = 0;
        ++cycles[i];
        return true;
    }
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

    // Helper method for Factorize(int[], int). Factorizes n; assumes it's odd.
    private static void FactorizeOdd(this int[] primes,
                                     Dictionary<int, int> factorization, int n)
    {
        var sqrt = n.Sqrt();
        foreach (var p in primes.Skip(1).TakeWhile(q => q <= sqrt)) {
            if (n % p == 0) {
                var count = 1;
                while ((n /= p) % p == 0) ++count;
                factorization.Add(p, count);

                if (n == 1) return;
            }
        }

        // what remains (since n != 1 here) is a single prime factor > sqrt
        factorization.Add(n, 1);
    }

    // For p in primes, primes.Factorize(n)[p] is the number of factors of p
    // that may be extracted from n by division (n > 0). primes must consist of
    // the first primes.Length prime numbers, sorted increasingly.
    private static Dictionary<int, int> Factorize(this int[] primes, int n)
    {
        var twos = 0; // we will quickly pull out all factors of 2
        for (; (n & 1) == 0; n >>= 1) ++twos;

        var factorization = new Dictionary<int, int>();
        if (twos != 0) factorization.Add(2, twos);
        if (n != 1) primes.FactorizeOdd(factorization, n);
        return factorization;
    }

    // Prime-factorizes n, assigns a sorted array of the prime factors to
    // prime_support, assigns an array of their corresponding exponents to
    // exponents, and returns the length of these arrays (i.e., the number of
    // prime factors with nonzero powers).
    private static int Factorize(this int[] primes, int n,
                                 out int[] prime_support, out int[] exponents)
    {
        var factorization = primes.Factorize(n);
        var len = factorization.Count;
        prime_support = new int[len];
        exponents = new int[len];

        var i = 0;
        foreach (var pair in factorization.OrderBy(pair => pair.Key)) {
            prime_support[i] = pair.Key;
            exponents[i++] = pair.Value;
        }

        return len;
    }

    // Yields divisors of n > 0. Helper method for SumProperDivisors().
    private static IEnumerable<int> GetDivisors(this int[] primes, int n)
    {
        int[] max_exponents;
        var len = primes.Factorize(n, out primes, out max_exponents);
        var exponents = new int[len];

        do {
            var divisor = 1;

            for (var i = 0; i != len; ++i)
                for (var e = exponents[i]; e != 0; --e) divisor *= primes[i];

            yield return divisor;
        }
        while (Combinatorics.Advance(len, exponents, max_exponents));
    }

    // Sums the distinct proper integer divisors of n. primes must begin with
    // all the prime numbers up to sqrt(n).
    internal static int SumProperDivisors(this int[] primes, int n)
            => primes.GetDivisors(n).Sum() - n;

    internal static IEnumerable<int> GetProperDivisorSums(this int[] primes,
                                                          int max)
    {
        yield return 0; // 0 has 0 proper divisors
        yield return 0; // 1 has 0 proper divisors

        for (var i = 2; i <= max; ++i)
            yield return primes.SumProperDivisors(i);
    }
}

internal static class Solution {
    private static IEnumerable<int> GetAmicables(int dmax, int nmax)
    {
        var primes = Primes.To(Math.Max(dmax, nmax).Sqrt());
        var d = primes.GetProperDivisorSums(nmax).ToArray();

        for (var i = 2; i <= nmax; ++i) {
            if (d[i] > nmax ? primes.SumProperDivisors(d[i]) == i
                            : d[d[i]] == i && d[i] != i)
                yield return i;
        }
    }

    private static Dictionary<int, int> GetAmicableRangeSums(int dmax,
                                                             int[] ns)
    {
        ns = ns.OrderBy(n => n).Distinct().ToArray();
        var a = GetAmicables(dmax, ns[ns.Length - 1]).ToArray();
        var sums = new Dictionary<int, int>();

        var i = 0;
        var s = 0;
        foreach (var n in ns) {
            for (; i != a.Length && a[i] < n; ++i) s += a[i];
            sums.Add(n, s);
        }

        return sums;
    }

    private static int Get() => int.Parse(Console.ReadLine());

    private static void Main()
    {
        // Maximum allowed value of Enumerable.Range(1, 100000)
        //                          .Select(n => primes.SumProperDivisors(n))
        //                          .Max()
        const int dmax = 304920;

        var ns = Enumerable.Range(0, Get()).Select(i => Get()).ToArray();
        var sums = GetAmicableRangeSums(dmax, ns);
        foreach (var n in ns) Console.WriteLine(sums[n]);
    }
}
