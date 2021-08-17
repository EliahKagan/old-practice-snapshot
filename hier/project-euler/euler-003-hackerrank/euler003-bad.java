import java.util.Scanner;

final class Arith {
    static int sqrt32(final int n)
    {
        return (int)Math.round(Math.floor(Math.sqrt(n)));
    }
    
    static long sqrt64(final long n)
    {
        return Math.round(Math.floor(Math.sqrt(n)));
    }
    
    static int sqrt64to32(final long n)
    {
        return (int)sqrt64(n);
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
    
    static long[] sieve(final int n) // returns array of primes up to n
    {
        final boolean[] a = new boolean[n + 1];
        final int count = rawSieve(a);
        
        final long[] primes = new long[count];
        primes[0] = 2L;
        
        int p = 3;
        for (int k = 1; k != count; ++k) {
            while (a[p]) p += 2;
            primes[k] = (long)p;
        }
        
        return primes;
    }
    
    // Computes the largest prime divisor of n > 1, provided primes contains at
    // least all prime numbers up to the square root of n, and no non-primes.
    static long maxPrimeDivisor(final long[] primes, long n)
    {
        while ((n & 1L) == 0L) n >>>= 1L; // optimization, removes factors of 2
        if (n == 1L) return 2L;
        
        final long sqrt = sqrt64(n);
        
        for (int k = 1; k < primes.length; ++k) {
            final long p = primes[k];
            if (p > sqrt) break;
            
            if (n % p != 0L) continue;
            
            do n /= p;
            while (n % p == 0L);
            
            if (n == 1L) return p;
        }
        
        return n; // what remains must be a single prime factor > sqrt(orig. n)
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class Solution {
    // Fills the values array with values scanned, one per line, from sc.
    // Returns the largest of the values scanned (i.e., values's new max).
    private static long readValues(final Scanner sc, final long[] values)
    {
        long max = 0L;
        
        for (int i = 0; i != values.length; ++i) {
            final long elem = sc.nextLong();
            if (max < elem) max = elem;
            values[i] = elem;
        }
        
        return max;
    }
    
    public static void main(final String[] args)
    {
        final long[] values;
        final long max;
        
        try (final Scanner sc = new Scanner(System.in)) {
            values = new long[sc.nextInt()];
            max = readValues(sc, values);
        }
        
        final long[] primes = Arith.sieve(Arith.sqrt64to32(max));
        
        for (final long n : values)
            System.out.println(Arith.maxPrimeDivisor(primes, n));
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
