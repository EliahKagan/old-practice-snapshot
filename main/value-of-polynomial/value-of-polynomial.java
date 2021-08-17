import java.util.Scanner;

final class Solution {
    private static final long M = 1_000_000_007L;
    
    private static long[] readPolynomial(final Scanner sc)
    {
        final long[] a = new long[sc.nextInt()];
        for (int i = a.length; --i >= 0; ) a[i] = sc.nextLong();
        return a;
    }
    
    private static long evalPolynomial(final long[] a, final long x)
    {
        long y = 0L, p = 1L;
        
        for (final long k : a) {
            y = (y + k * p) % M;
            p = (p * x) % M;
        }
        
        return y;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final long[] a = readPolynomial(sc);
                System.out.println(evalPolynomial(a, sc.nextLong()));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
