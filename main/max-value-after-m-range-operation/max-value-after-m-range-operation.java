import java.util.Scanner;

final class Solution {
    private static int computeMaxPartialSum(final int[] deltas)
    {
        int best = 0, cur = 0;
        for (int d : deltas) best = Math.max(best, cur += d);
        return best;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int[] deltas = new int[sc.nextInt() + 1];

                for (int m = sc.nextInt(); m > 0; --m) {
                    final int a = sc.nextInt(), b = sc.nextInt(), k = sc.nextInt();
                    deltas[a] += k;
                    deltas[b + 1] -= k;
                }

                System.out.println(computeMaxPartialSum(deltas));
            }
        }
    }
    
    private Solution() { throw new AssertionError(); }
}
