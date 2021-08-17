import java.util.Scanner;

final class Solution {
    private static final long MOD = 1_000_000_007L;
    
    private static long computeModifiedFibonacci(
            final long n, final long a, final long b, final long c)
    {
        switch ((int)((n - 1) % 6L)) {
            case 0:     return a + b;
            case 1:     return b + c;
            case 2:     return c - a;
            case 3:     return -a - b;
            case 4:     return -b - c;
            case 5:     return a - c;
            default:    throw new IllegalArgumentException();
        }
    }
    
    private static void run(final Scanner sc)
    {
        final long n = sc.nextLong();
        final long a = sc.nextLong(), b = sc.nextLong(), c = sc.nextLong();
        System.out.println((computeModifiedFibonacci(n, a, b, c) + MOD) % MOD);
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) run(sc);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
