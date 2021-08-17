final class Arith {
    private static int rawSieve(final boolean[] a) // returns count of primes
    {
        final int n = a.length - 1;
        int count = n - n / 2; // evens, including 0 but not 2, aren't prime
        
        final int imax = (int)Math.sqrt(n);
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
        
        for (int p = 1, k = 1; k != count; ++k) {
            while (a[p += 2]) { }
            primes[k] = (long)p;
        }
        
        return primes;
    }
    
    private static boolean hasSmallFactor(final long[] primes, final long n)
    {
        final long pmax = (long)Math.sqrt(n);
        
        for (final long p : primes) {
            if (p > pmax) break;
            if (n % p == 0) return true;
        }
        
        return false;
    }
    
    static boolean isPrime(final long[] primes, final long n)
    {
        final int i = java.util.Arrays.binarySearch(primes, n);
        return i >= 0 || (~i == primes.length && !hasSmallFactor(primes, n));
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class Solution {
    public static void main(final String[] args)
    {
        final long[] primes = Arith.sieve((int)Math.sqrt(1L << 32L));
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final boolean ans = Arith.isPrime(primes, sc.nextLong());
                System.out.println(ans ? "YES" : "NO");
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
