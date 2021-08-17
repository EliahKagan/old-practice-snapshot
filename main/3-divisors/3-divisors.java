import java.util.stream.IntStream;

final class Arith  {
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
    
    static IntStream sieve(final int n) // streams primes up to n
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
    
    private Arith() { } // the Arith class should not be instantiated
}

final class Solution {
    private static final int NMAX = 1_000_000_000;
    
    private static final int[] primeSquares
            = Arith.sieve(Arith.sqrt(NMAX)).map(p -> p * p).toArray();
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int n = sc.nextInt();
                final int i = java.util.Arrays.binarySearch(primeSquares, n);
                System.out.println(i < 0 ? ~i : i + 1);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
