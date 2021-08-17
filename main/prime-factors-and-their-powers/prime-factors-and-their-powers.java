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
    
    private static void printPair(final int k, final int q,
                                  final boolean print_leading_sep)
    {
        if (print_leading_sep) System.out.print(" ");
        System.out.print(k);
        System.out.print(" ");
        System.out.print(q);
    }
    
    // Prints the highest q for which k^q divides n, or nothing if q = 0.
    // Assumes k > 0, n > 1. Returns n / k^q.
    private static int printContribution(int n, final int k,
                                         final boolean print_leading_sep)
    {
        int q = 0;
        for (; n % k == 0; n /= k) ++q;
        if (q != 0) printPair(k, q, print_leading_sep);
        return n;
    }
    
    static void printPrimeFactorization(final int[] primes, int n)
    {
        if (n == 2) printPair(2, 1, false);
        else {
            boolean print_leading_sep = false;
            final int sqrt = sqrt32(n);
            
            for (final int k : primes) {
                if (k > sqrt) break;
                final int nn = printContribution(n, k, print_leading_sep);
                if (n != nn) {
                    n = nn;
                    print_leading_sep = true;
                }
            }
            
            if (n != 1) // what remains must be a single prime factor > sqrt
                printPair(n, 1, print_leading_sep);
        }
        
        System.out.println();
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
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            final int[] nums = new int[sc.nextInt()];
            final int max = readValues(sc, nums);
            final int[] primes = Arith.sieve(Arith.sqrt32(max));
            for (final int n : nums) Arith.printPrimeFactorization(primes, n);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
