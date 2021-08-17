import java.util.*;

final class Solution {
    private static int[] get(final Scanner sc)
    {
        final int[] a = new int[sc.nextInt()];
        for (int i = 0; i != a.length; ++i) a[i] = sc.nextInt();
        return a;
    }
    
    private static int gcd(final int m, final int n)
    {
        return n == 0 ? m : gcd(n, m % n);
    }
    
    private static int gcd(final int[] a)
    {
        int acc = a[0];
        for (int i = 1; i != a.length; ++i) acc = gcd(acc, a[i]);
        return acc;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int[] a = get(sc);
                Arrays.sort(a);
                System.out.println(gcd(a));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
