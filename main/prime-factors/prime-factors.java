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
    
    static void printPrimeDivisors(final int[] primes, int n)
    {
        String sep = "";
        
        if ((n & 1) == 0) { // optimization to remove factors of 2
            System.out.print(2);
            sep = " ";
            
            do n >>>= 1;
            while ((n & 1) == 0);
        }
        
        final int sqrt = sqrt32(n);
        
        for (int k = 1; k < primes.length; ++k) {
            final int p = primes[k];
            if (p > sqrt) break;
            
            if (n % p != 0) continue;
            
            System.out.format("%s%d", sep, p);
            sep = " ";
            
            do n /= p;
            while (n % p == 0);
        }
        
        if (n != 1) // what remains must be a single prime factor > sqrt
            System.out.format("%s%d", sep, n);
        
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
