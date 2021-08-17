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
    
    // Computes the largest prime factor of n > 1, provided primes contains at
    // least all prime numbers <= sqrt(n) and no non-prime numbers.
    static long maxPrimeDivisor(final long[] primes, long n)
    {
        while ((n & 1L) == 0L) n >>>= 1L; // optimization, removes factors of 2
        if (n == 1L) return 2L;
        
        final long sqrt = sqrt64(n);
        
        for (int i = 1; i != primes.length && primes[i] <= sqrt; ++i) {
            if (n % primes[i] != 0L) continue;
            
            do n /= primes[i];
            while (n % primes[i] == 0L);
            
            if (n == 1L) return primes[i];
        }
        
        return n; // what remains must be a single prime factor > sqrt(orig. n)
    }
    
    private Arith() { } // the Arith class should not be instantiated
}

final class Solution {
    static long[] readValues()
    {
        try (final Scanner sc = new Scanner(System.in)) {
            return IntStream.range(0, sc.nextInt())
                            .mapToLong(i -> sc.nextLong())
                            .toArray();
        }
    }
    
    public static void main(final String[] args)
    {
        final long[] values = readValues();
        final long max = LongStream.of(values).max().getAsLong();
        
        final long[] primes = Arith.sieve(Arith.sqrt64to32(max)).toArray();
        
        for (final long n : values)
            System.out.println(Arith.maxPrimeDivisor(primes, n));
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
