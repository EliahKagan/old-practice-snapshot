import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.IntStream;

final class Arith {
    static long product(final int[] values)
    {
        long p = 1L;
        for (final int elem : values) p *= elem;
        return p;
    }
    
    static int sqrt32(final int n)
    {
        return (int)Math.round(Math.floor(Math.sqrt(n)));
    }
    
    private static int rawSieve(final boolean[] a) // returns count of primes
    {
        final int n = a.length - 1;
        int count = n - n / 2; // evens, including 0 but not 2, aren't prime
        
        final int imax = sqrt32(n);
        for (int i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                final int jstep = i * 2;
                for (int j = i * i; j <= n; j += jstep) {
                    if (a[j]) continue;
                    a[j] = true;
                    --count;
                }
            }
        }
        
        return count;
    }
    
    static int[] sieve(final int n) // returns array of primes up to n
    {
        final boolean[] a = new boolean[n + 1];
        final int count = rawSieve(a);
        
        final int[] primes = new int[count];
        primes[0] = 2;
        
        for (int p = 1, k = 1; k != count; ++k) {
            while (a[p += 2]) { }
            primes[k] = p;
        }
        
        return primes;
    }
    
    // Helper method for factorize(). Factorizes n, assuming that it is odd.
    private static void factorizeOdd(final int[] primes,
                                     final int[] factorization, int n)
    {
        final int sqrt = sqrt32(n);
        
        int i = 1;
        for (; primes[i] <= sqrt; ++i) {
            if (n % primes[i] != 0) continue;

            do {
                ++factorization[i];
                n /= primes[i];
            }
            while (n % primes[i] == 0);
            
            if (n == 1) return;
        }
        
        // what remains (since n != 1 here) is a single prime factor > sqrt
        ++factorization[Arrays.binarySearch(primes, i, primes.length, n)];
    }
    
    // Increments factorization[i] for each factor of primes[i] in n (n > 0).
    // primes must the first primes.length prime numbers, sorted increasingly.
    static void factorize(final int[] primes, final int[] factorization, int n)
    {
        while ((n & 1) == 0) { // quickly pull out all factors of 2
            n >>>= 1;
            ++factorization[0];
        }
        
        if (n != 1) factorizeOdd(primes, factorization, n);
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class Factorials {
    // computeRawDivisorCounts(sorted_values)[n] is the number of distinct
    // divisors of the factorial of n when sorted_values contains n, and
    // zero otherwise. This is a helper function for computeDivisorCounts().
    private static long[] computeRawDivisorCounts(final int[] sorted_values)
    {
        final int max = sorted_values[sorted_values.length - 1];
        final int[] primes = Arith.sieve(max);
        
        final int[] choices = new int[primes.length];
        Arrays.fill(choices, 1);
        
        final long[] raw_counts = new long[max + 1];
        raw_counts[1] = 1L; // a simple optimization (1! has just 1 factor)
        
        int i = (sorted_values[0] == 1 ? 1 : 0);
        for (int n = 2; n != raw_counts.length; ++n) {
            Arith.factorize(primes, choices, n);
            
            if (n == sorted_values[i]) {
                raw_counts[n] = Arith.product(choices);
                ++i;
            }
        }
        
        return raw_counts;
    }
    
    // computeDivisorCounts(values)[i] is the number of distinct divisors of
    // the factorial of values[i].
    static long[] computeDivisorCounts(final int[] values)
    {
        final long[] raw_counts = computeRawDivisorCounts(
                IntStream.of(values).sorted().distinct().toArray());
        
        final long[] counts = new long[values.length];
        for (int i = 0; i != values.length; ++i)
            counts[i] = raw_counts[values[i]];
        
        return counts;
    }
    
    private Factorials() { } // the Factorials class should not be instantiated
}

final class Solution {
    private static int[] readValues()
    {
        try (final Scanner sc = new Scanner(System.in)) {
            final int[] values = new int[sc.nextInt()];
            for (int i = 0; i != values.length; ++i) values[i] = sc.nextInt();
            return values;
        }
    }
    
    public static void main(final String[] args)
    {
        for (final long k : Factorials.computeDivisorCounts(readValues()))
            System.out.println(k);
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
