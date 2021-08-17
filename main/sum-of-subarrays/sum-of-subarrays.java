import java.util.Scanner;

final class Solution {
    private static final long MOD = 1_000_000_007;
    
    private static long readContiguousSubarraySumSum(final Scanner sc)
    {
        final int n = sc.nextInt();
        
        return java.util.stream.IntStream.range(0, n)
                .mapToLong(k -> (k + 1) * (n - k) * sc.nextLong() % MOD)
                .sum() % MOD;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(readContiguousSubarraySumSum(sc));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
