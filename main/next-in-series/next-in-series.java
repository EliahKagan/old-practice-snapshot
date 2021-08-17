import java.util.Scanner;

final class Solution {
    private static final long NO_MATCH = -99999L, MOD = 1_000_000_007L;
    
    private static long gcd(final long m, final long n)
    {
        return n == 0L ? m : gcd(n, m % n);
    }
    
    private static boolean isArithmetic(final long[] a)
    {
        final long d = a[1] - a[0];
        
        for (int i = 2; i != a.length; ++i)
            if (a[i] - a[i - 1] != d) return false;
        
        return true;
    }
    
    private static long nextArithmetic(final long x, final long y)
    {
        return y * 2L - x;
    }
    
    private static boolean isGeometric(final long[] a)
    {
        for (int i = 0; i != a.length; ++i)
            if (a[i] == 0L) return false;
        
        final long reduce_factor = gcd(a[1], a[0]);
        final long numerator = a[1] / reduce_factor;
        final long denominator = a[0] / reduce_factor;
        
        for (int i = 2; i != a.length; ++i) {
            final long product = a[i - 1] * numerator;
            if (product % denominator != 0L || product / denominator != a[i])
                return false;
        }
        
        return true;
    }
    
    private static long nextGeometric(final long x, final long y) // rounds up
    {
        final long reduce_factor = gcd(y, x);
        final long numerator = y / reduce_factor;
        final long denominator = x / reduce_factor;
        
        final long product = y * numerator, floor = product / denominator;
        return product % denominator == 0L ? floor : floor + 1L;
    }
    
    private static boolean isFibonacci(final long[] a)
    {
        for (int i = 2; i != a.length; ++i)
            if (a[i - 2] + a[i - 1] != a[i]) return false;
        
        return true;
    }
    
    private static long nextFibonacci(final long x, final long y)
    {
        return x + y;
    }
    
    private static long computeNext(final long[] a)
    {
        final long x = a[a.length - 2], y = a[a.length - 1];
        
        if (isArithmetic(a)) return nextArithmetic(x, y);
        if (isGeometric(a)) return nextGeometric(x, y);
        if (isFibonacci(a)) return nextFibonacci(x, y);
        return NO_MATCH;
    }
    
    private static long[] get(final Scanner sc)
    {
        final long[] a = new long[sc.nextInt()];
        for (int i = 0; i != a.length; ++i) a[i] = sc.nextLong();
        return a;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(computeNext(get(sc)) % MOD);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
