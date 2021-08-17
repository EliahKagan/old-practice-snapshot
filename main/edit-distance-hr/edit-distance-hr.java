import java.util.Scanner;

final class Solution {
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(distance(sc.next(), sc.next()));
        }
    }

    // Wagner-Fischer algorithm with space optimization.
    private static int distance(final String s, final String t) {
        return s.length() < t.length() ? do_distance(t, s) : do_distance(s, t);
    }

    // Helper function for distance(String, String).
    private static int do_distance(final String s, final String t) {
        int[] pre = new int[t.length() + 1];
        int[] cur = iota(pre.length);

        for (int i = 1; i <= s.length(); ++i) {
            {
                final int[] tmp = pre;
                pre = cur;
                cur = tmp;
            }

            cur[0] = i;

            for (int j = 1; j <= t.length(); ++j) {
                if (s.charAt(i - 1) == t.charAt(j - 1))
                    cur[j] = pre[j - 1];
                else
                    cur[j] = 1 + min3(cur[j - 1], pre[j], pre[j - 1]);
            }
        }

        return cur[t.length()];
    }

    //  Obtains an array of ascending consecutive integers.
    private static int[] iota(final int length) {
        final int[] ret = new int[length];
        for (int i = 0; i < length; ++i) ret[i] = i;
        return ret;
    }

    private static int min3(final int x, final int y, final int z) {
        return Math.min(Math.min(x, y), z);
    }

    private Solution() {
        throw new AssertionError();
    }
}
