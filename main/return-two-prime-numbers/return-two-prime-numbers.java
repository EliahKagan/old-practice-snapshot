import java.util.stream.IntStream;

final class Primes {
    private static int sqrt32(final int n)
    {
        return (int)Math.round(Math.floor(Math.sqrt(n)));
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
        
        final int imax = sqrt32(n);
        for (int i = 3; i <= imax; i += 2) {
            if (!a[i]) {
                final int jstep = i * 2;
                for (int j = i * i; j <= n; j += jstep) a[j] = true;
            }
        }
        
        return IntStream.concat(IntStream.of(2),
                                rangeClosed(3, n, 2).filter(k -> !a[k]));
    }
    
    static int[] to(final int n) // returns array of all primes <= max(n, 2)
    {
        return sieve(n).toArray();
    }
    
    private Primes() { } // the Primes class should not be instantiated
}

final class Solution {
    private static void printPairWithSum(final int[] a, final int n)
    {
        for (int i = 0; i != a.length; ++i) {
            final int key = n - a[i];
            if (key < a[i]) break;
            
            final int j = java.util.Arrays.binarySearch(a, i, a.length, key);
            if (j >= 0) {
                System.out.format("%d %d", a[i], a[j]);
                break;
            }
        }
        
        System.out.println();
    }
    
    public static void main(final String[] args)
    {
        final int max = 10000;
        final int[] primes = Primes.to(max);
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                printPairWithSum(primes, sc.nextInt());
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
