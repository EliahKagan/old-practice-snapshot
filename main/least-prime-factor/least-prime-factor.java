import java.util.Scanner;

final class Arith {
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
    
    private static int leastPrimeDivisor(final int[] primes, final int n)
    {
        for (final int p : primes)      // naive unoptimized algorithm
            if (n % p == 0) return p;
        
        return n;
    }
    
    static int[] computeLeastPrimeDivisors(final int[] primes, final int n)
    {
        final int[] a = new int[n + 1];
        a[1] = 1;
        for (int i = 2; i <= n; ++i) a[i] = leastPrimeDivisor(primes, i);
        return a;
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class Solution {
    // Fills the values array with values scanned, one per line, from sc.
    // Returns the largest of the values scanned (i.e., values's new max).
    private static int readValues(final Scanner sc, final int[] values)
    {
        int max = 0;
        
        for (int i = 0; i != values.length; ++i) {
            final int elem = sc.nextInt();
            if (max < elem) max = elem;
            values[i] = elem;
        }
        
        return max;
    }
    
    private static void printSlice(final int[] values, int low, final int high)
    {
        if (low <= high) {
            System.out.print(values[low]);
            while (++low <= high) System.out.format(" %d", values[low]);
        }
        
        System.out.println();
    }
    
    public static void main(final String[] args)
    {
        final int[] bounds;
        final int max;
        
        try (final Scanner sc = new Scanner(System.in)) {
            bounds = new int[sc.nextInt()];
            max = readValues(sc, bounds);
        }
        
        final int[] primes = Arith.sieve(Arith.sqrt32(max));
        final int[] divisors = Arith.computeLeastPrimeDivisors(primes, max);
        
        for (final int n : bounds) printSlice(divisors, 1, n);
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
