import java.util.stream.IntStream;

final class Arith {
    static int sqrt(final int n)
    {
        return (int)Math.sqrt(n); // simple cast from double OK for 32-bit ints
    }
    
    private static IntStream rangeClosed(
            final int startInclusive, final int endInclusive, final int step)
    {
        return IntStream.rangeClosed(0, (endInclusive - startInclusive) / step)
                        .map(k -> startInclusive + k * step);
    }
    
    private static IntStream sieve(final int n) // streams primes up to n
    {
        final boolean[] a = new boolean[n + 1];
        
        final int imax = sqrt(n);
        for (int i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                final int jstep = i * 2;
                for (int j = i * i; j <= n; j += jstep) a[j] = true;
            }
        }
        
        return IntStream.concat(IntStream.of(2),
                                rangeClosed(3, n, 2).filter(k -> !a[k]));
    }
    
    static int[] primesTo(final int n) // returns all primes <= max(n, 2)
    {
        return sieve(n).toArray();
    }
    
    private static boolean hasSmallFactor(final int[] primes, final int n)
    {
        final int pmax = sqrt(n);
        
        for (final int p : primes) {
            if (p > pmax) break;
            if (n % p == 0) return true;
        }
        
        return false;
    }
    
    static boolean isPrime(final int[] primes, final int n)
    {
        final int i = java.util.Arrays.binarySearch(primes, n);
        return i >= 0 || (~i == primes.length && !hasSmallFactor(primes, n));
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class Solution {
    public static void main(final String[] args)
    {
        final int[] primes = Arith.primesTo(Arith.sqrt(Integer.MAX_VALUE));
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final boolean ans = Arith.isPrime(primes, sc.nextInt());
                System.out.println(ans ? "YES" : "NO");
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
