import java.util.Scanner;

final class PairPrinter implements AutoCloseable {
    private boolean print_leading_sep = false;
    
    public void print(final int x, final int y)
    {
        if (print_leading_sep) System.out.format(" %d %d", x, y);
        else {
            System.out.format("%d %d", x, y);
            print_leading_sep = true;
        }
    }
    
    @Override
    public void close()
    {
        System.out.println();
    }
}

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
    
    // Prints the highest q for which k^q divides n, or nothing if q = 0.
    // Assumes k > 0, n > 1. Returns n / k^q.
    private static int printContribution(final PairPrinter pp,
                                         int n, final int k)
    {
        int q = 0;
        for (; n % k == 0; n /= k) ++q;
        if (q != 0) pp.print(k, q);
        return n;
    }
    
    static void printPrimeFactorization(final int[] primes, int n)
    {
        try (final PairPrinter pp = new PairPrinter()) {
            if (n == 2) {
                pp.print(2, 1);
                return;
            }
            
            final int sqrt = sqrt32(n);

            for (final int k : primes) {
                if (k > sqrt) break;
                n = printContribution(pp, n, k);
            }

            if (n != 1) pp.print(n, 1); // must be a single prime factor > sqrt
        }
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
