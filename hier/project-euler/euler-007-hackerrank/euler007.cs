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

internal static class Solution {
    private static int Parse() => int.Parse(Console.ReadLine());

    private static void Main()
    {
        const int n = 104743; // the 10001st prime number
        var primes = Arith.Primes(n);

        for (var t = Parse(); t > 0; --t)
            Console.WriteLine(primes[Parse() - 1]);
    }
}
