import java.util.Scanner;

final class Solution {
    private static long[] getRecord(final Scanner sc)
    {
        final long[] a = new long[sc.nextInt()];
        for (int i = 0; i != a.length; ++i) a[i] = sc.nextLong();
        return a;
    }
    
    private static long sum(final long[] a)
    {
        long acc = 0L;
        for (final long elem : a) acc += elem;
        return acc;
    }
    
    // Performs k negations on elements of a, which must be sorted
    // nondecreasingly, in such a way as to maximuze the sum over a.
    private static void doMaximizingNegations(final long[] a, int k)
    {
        if (k < 0) {
            throw new IllegalArgumentException(
                    "can't negate fewer than 0 elements");
        }
        
        if (a.length == 0 && k % 2 != 0) {
            throw new IllegalArgumentException(
                    "can't negate more than 0 elements of an empty array");
        }
        
        int i = 0;
        for (; k != 0 && i != a.length && a[i] < 0L; ++i, --k) a[i] = -a[i];
        if (k % 2 == 0) return; // "negate" any element an even number of times
        
        if (i == a.length || (i != 0 && a[i - 1] < a[i]))
            a[i - 1] = -a[i - 1]; // restore the negative element closest to 0
        else
            a[i] = -a[i];         // negate the nonnegative element closes to 0
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final long[] a = getRecord(sc);
                java.util.Arrays.sort(a);
                
                final int k = sc.nextInt();
                doMaximizingNegations(a, k);
                
                System.out.println(sum(a));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
