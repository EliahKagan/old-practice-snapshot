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
}

internal static class UnitTest {
    private static void Main()
    {
        const int max = 100000;
        
        var primes = Primes.To(max.Sqrt());
        
        Enumerable.Range(1, max)
                  .Select(n => primes.SumProperDivisors(n))
                  .Max()
                  .Dump();
    }
}