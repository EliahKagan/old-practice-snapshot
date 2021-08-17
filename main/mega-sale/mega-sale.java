import java.util.Scanner;
import java.util.stream.IntStream;

final class Solution {
    private static int getMaximumEarnings(final Scanner sc,
                                          final int n, final int m)
    {
        return -IntStream.range(0, n)
                         .map(i -> sc.nextInt())
                         .filter(k -> k < 0)
                         .sorted()
                         .limit(m)
                         .sum();
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int n = sc.nextInt(), m = sc.nextInt();
                System.out.println(getMaximumEarnings(sc, n, m));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instnatiated
}
