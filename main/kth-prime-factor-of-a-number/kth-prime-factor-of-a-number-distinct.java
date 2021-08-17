import java.util.Scanner;
import java.util.stream.IntStream;
import java.util.stream.LongStream;

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
    
    private static IntStream rangeClosed(
            final int startInclusive, final int endInclusive, final int step)
    {
        return IntStream.rangeClosed(0, (endInclusive - startInclusive) / step)
                        .map(k -> startInclusive + k * step);
    }
    
    static LongStream sieve(final int n) // streams primes up to n
    {
        final boolean[] a = new boolean[n + 1];
        
        final int imax = sqrt32(n);
        for (int i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                final int jstep = i * 2;
                for (int j = i * i; j <= n; j += jstep) a[j] = true;
            }
        }
        
        return LongStream.concat(LongStream.of(2L),
                rangeClosed(3, n, 2).filter(k -> !a[k]).asLongStream());
    }
    // Returns the kth prime divisor or n, or -1 if n has no kth prime divisor,
    // provided pprimes contains at least all prime numbers <= sqrt(n) and no
    // non-prime numbers.
    static long kthPrimeDivisor(final long[] primes, long n, long k)
    {
        if (n < 0L || k < 1) throw new IllegalArgumentException();
        if (n == 0L) return -1L;
        
        for (final long p : primes) {
            if (n % p != 0L) continue;
            if (--k == 0) return p;
            
            do n /= p;
            while (n % p == 0L);
        }
        
        return k == 1 && n != 1L ? n : -1L;
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class Solution {
    private static void run(final long[] ns, final int[] ks, final long nmax)
    {
        final int s = Math.max(Arith.sqrt64to32(nmax), 3);
        final long[] primes = Arith.sieve(s).toArray();
        
        for (int i = 0; i != ns.length; ++i)
            System.out.println(Arith.kthPrimeDivisor(primes, ns[i], ks[i]));
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            final long[] ns = new long[sc.nextInt()];
            final int[] ks = new int[ns.length];
            
            long nmax = 0L;
            for (int i = 0; i != ns.length; ++i) {
                nmax = Math.max(nmax, ns[i] = sc.nextLong());
                ks[i] = sc.nextInt();
            }
            
            run(ns, ks, nmax);
        }
    }
    
    private Solution() { } // the Solution class should not be instantated
}
