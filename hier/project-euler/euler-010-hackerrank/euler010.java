import java.util.Scanner;

final class Algo { // some algorithms on int[]
    private static int findMaxLessOrEqual(final long[] seq, final long key,
                                          final int low, final int high)
    {
        if (high < low) return high;
        
        final int mid = low + (high - low) / 2;
        
        if (key < seq[mid]) return findMaxLessOrEqual(seq, key, low, mid - 1);
        if (key > seq[mid]) return findMaxLessOrEqual(seq, key, mid + 1, high);
        return mid;
    }
    
    static int findMaxLessOrEqual(final long[] seq, final long key)
    {
        return findMaxLessOrEqual(seq, key, 0, seq.length - 1);
    }
    
    static long[] runningSum(final long[] seq)
    {
        final long[] sums = new long[seq.length];
        
        long acc = 0L;
        for (int i = 0; i != seq.length; ++i) sums[i] = (acc += seq[i]);
        
        return sums;
    }
    
    private Algo() { } // the Algo class should not be instantiated
}

final class Arith {
    private static int sqrt32(final int n)
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
    
    static long[] sieve(final long n) // returns array of primes up to n
    {
        final boolean[] a = new boolean[(int)(n + 1L)];
        final int count = rawSieve(a);
        
        final long[] primes = new long[count];
        primes[0] = 2L;
        
        for (int p = 1, k = 1; k != count; ++k) {
            while (a[p += 2]) { }
            primes[k] = (long)p;
        }
        
        return primes;
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class Solution {
    // Fills the values array with values scanned, one per line, from sc.
    // Returns the largest of the values scanned (i.e., values's new max).
    private static long readValues(final Scanner sc, final long[] values)
    {
        long max = 0;
        
        for (int i = 0; i != values.length; ++i) {
            final long elem = sc.nextInt();
            if (max < elem) max = elem;
            values[i] = elem;
        }
        
        return max;
    }
    
    public static void main(final String[] args)
    {
        final long[] bounds;
        final long max;
        
        try (final Scanner sc = new Scanner(System.in)) {
            bounds = new long[sc.nextInt()];
            max = readValues(sc, bounds);
        }
        
        final long[] primes = Arith.sieve(max), sums = Algo.runningSum(primes);
        
        for (final long n : bounds)
            System.out.println(sums[Algo.findMaxLessOrEqual(primes, n)]);
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
