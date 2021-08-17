import java.util.stream.IntStream;
import java.util.stream.LongStream;

final class Arith {
    private static IntStream rangeClosed(
            final int startInclusive, final int endInclusive, final int step)
    {
        return IntStream.rangeClosed(0, (endInclusive - startInclusive) / step)
                        .map(k -> startInclusive + k * step);
    }
    
    private static LongStream sieve(final int n) // streams primes up to n
    {
        final boolean[] a = new boolean[n + 1];
        
        final int imax = (int)Math.sqrt(n);
        for (int i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                final int jstep = i * 2;
                for (int j = i * i; j <= n; j += jstep) a[j] = true;
            }
        }
        
        return LongStream.concat(LongStream.of(2L),
                rangeClosed(3, n, 2).filter(k -> !a[k]).asLongStream());
    }
    
    static long[] primesTo(final int n)
    {
        return sieve(n).toArray();
    }
    
    static long countSquareDivisors(final long[] primes, long n)
    {
        long ret = 1L; // 1 is a square number, and it divides every n
        
        if (n != 1L) {
            for (final long p : primes) {
                if (p * p > n) break;
                
                if (n % p == 0L) {
                    long k = 1L;
                    while ((n /= p) % p == 0L) ++k;
                    ret *= 1L + k / 2L;
                    if (n == 1L) break;
                }
            }
        }
        
        return ret;
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class Solution {
    public static void main(final String[] args)
    {
        final int pmax = 1_000_000; // max n is 10**12; sqrt(10**12) == 10**6
        final long[] primes = Arith.primesTo(pmax);
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final long n = sc.nextLong();
                System.out.println(Arith.countSquareDivisors(primes, n));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
