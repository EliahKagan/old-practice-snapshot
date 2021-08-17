<Query Kind="Program" />

internal static class Int32Ex {
    // Casting from double extracts 32-bit integer square roots accurately.
    internal static uint Sqrt(this uint n) => (uint)Math.Sqrt(n);
}

internal static class Primes {
    private static IEnumerable<uint> Sieve(uint n) // yields primes up to n
    {
        var a = new bool[n + 1]; // false means not marked as composite

        var imax = n.Sqrt();
        for (var i = 3u; i <= imax; i += 2u) {
            if (!a[i]) {
                var jstep = i * 2u;
                for (var j = i * i; j <= n; j += jstep) a[j] = true;
            }
        }

        yield return 2u;
        for (var k = 3u; k <= n; k += 2u)
            if (!a[k]) yield return k;
    }

    internal static uint[] To(uint n) => Sieve(n).ToArray(); // all primes <= n
    
    private static bool HasSmallFactor(this uint[] primes, uint n)
    {
        var max = n.Sqrt();
        return primes.TakeWhile(p => p <= max).Any(p => n % p == 0u);
    }
    
    internal static bool IsPrime(this uint[] primes, uint n)
    {
        var i = Array.BinarySearch(primes, n);
        return i >= 0 || (~i == primes.Length && !primes.HasSmallFactor(n));
    }
}

internal static class UnitTest {
    private static void Main()
    {
        const uint max = 65536u; // uint.MaxValue.Sqrt()
        
        var primes = Primes.To(max);
        
        for (var t = int.Parse(Console.ReadLine()); t > 0; --t) {
            var ans = primes.IsPrime(uint.Parse(Console.ReadLine()));
            Console.WriteLine(ans ? "YES" : "NO");
        }
        
    }
}