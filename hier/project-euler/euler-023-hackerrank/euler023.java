import java.util.stream.IntStream;

final class Solution {
    private static int sumProperDivisors(final int n)
    {
        if (n < 3) return n - 1;
        
        int stop = (int)Math.sqrt(n), sum = 1;
        
        if (stop * stop == n) sum += stop;
        else ++stop;
        
        for (int i = 2; i != stop; ++i)
            if (n % i == 0) sum += i + n / i;
        
        return sum;
    }
    
    private static int[] getAbundantNumbers(final int max)
    {
        return IntStream.rangeClosed(1, max)
                        .filter(i -> sumProperDivisors(i) > i)
                        .toArray();
    }
    
    private static boolean hasPairWithSum(final int[] a, final int n)
    {
        for (int i = 0; i != a.length; ++i) {
            final int key = n - a[i];
            if (key < a[i]) break;
            
            if (java.util.Arrays.binarySearch(a, i, a.length, key) >= 0)
                return true;
        }
        
        return false;
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            final int[] ns = IntStream.range(0, sc.nextInt())
                                      .map(i -> sc.nextInt())
                                      .toArray();
            
            final int max = IntStream.of(ns).max().getAsInt();
            final int[] a = getAbundantNumbers(max);
            
            for (final int n : ns)
                System.out.println(hasPairWithSum(a, n) ? "YES" : "NO");
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
