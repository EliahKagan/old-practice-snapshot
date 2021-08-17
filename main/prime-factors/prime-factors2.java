import java.util.Scanner;

final class RecordPrinter implements AutoCloseable {
    private final String sep;
    private boolean first = true;
    
    public RecordPrinter(String sep)
    {
        this.sep = sep;
    }
    
    public void print(final int value)
    {
        if (first) {
            System.out.print(value);
            first = false;
        }
        else System.out.format("%s%d", sep, value);
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
    
    private static int printPrimeDivisorOf2(final RecordPrinter rp, int n)
    {
        if ((n & 1) == 0) {
            rp.print(2);
            
            do n >>>= 1; // optimization to quickly rmeove factors of 2
            while ((n & 1) == 0);
        }
        
        return n;
    }
    
    private static int printIntermediatePrimeDivisors(
            final RecordPrinter rp, final int[] primes, final int max, int n)
    {
        for (int k = 1; k < primes.length; ++k) {
            final int p = primes[k];
            if (p > max) break;

            if (n % p == 0) {
                rp.print(p);

                do n /= p;
                while (n % p == 0);
            }
        }
        
        return n;
    }
    
    static void printPrimeDivisors(final int[] primes, int n)
    {
        try (final RecordPrinter rp = new RecordPrinter(" ")) {
            n = printPrimeDivisorOf2(rp, n);
            n = printIntermediatePrimeDivisors(rp, primes, sqrt32(n), n);
            if (n != 1) rp.print(n); // must be single prime factor > sqrt
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
        final int[] values;
        final int max;
        
        try (final Scanner sc = new Scanner(System.in)) {
            values = new int[sc.nextInt()];
            max = readValues(sc, values);
        }
        
        final int[] primes = Arith.sieve(Arith.sqrt32(max));
        for (final int n : values) Arith.printPrimeDivisors(primes, n);
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
