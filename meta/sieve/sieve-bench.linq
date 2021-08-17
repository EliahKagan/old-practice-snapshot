<Query Kind="Program" />

internal static class Int32Ex {
    // Casting from double extracts square roots accurately from small ints.
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
}

internal static class UnitTest {
    private static void Main()
    {
        var nmax = uint.MaxValue.Sqrt();
        Console.Write($"Computing primes up to {nmax}...");
        var primes = Primes.To(nmax);
        Console.WriteLine(" done.");
        
        var len = primes.Length;
        var pmax = primes[len - 1];
        Console.WriteLine($"{len} primes found (highest is {pmax}).");
    }
}