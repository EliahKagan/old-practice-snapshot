import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

final class Subproblem {
    Subproblem(final int index, final int subtot) {
        this.index = index;
        this.subtot = subtot;
    }

    public boolean equals(final Subproblem other) {
        return other != null && index == other.index
                             && subtot == other.subtot;
    }

    public boolean equals(final Object obj) {
        return obj instanceof Subproblem && equals((Subproblem)obj);
    }

    private static final int HASH_SEED = 17;
    private static final int HASH_MULTIPLIER = 8191;

    public int hashCode() {
        int code = HASH_SEED;
        code = code * HASH_MULTIPLIER + index;
        code = code * HASH_MULTIPLIER + subtot;
        return code;
    }

    final int index;
    final int subtot;
}

interface Solver {
    long apply(int index, int subtot);
}

final class Solution {
    private static final long UNKNOWN = -1;

    private static long countWays(final int[] coins, final int total) {
        final Map<Subproblem, Long> memo = new HashMap<>();

        final Solver solve = new Solver() {
            public long apply(final int index, final int subtot) {
                if (subtot == 0) return 1L;
                if (index == coins.length) return 0L;

                final Subproblem key = new Subproblem(index, subtot);
                long count = memo.getOrDefault(key, UNKNOWN);
                if (count != UNKNOWN) return count;

                count = 0;
                final int coin = coins[index];

                final int nextIndex = index + 1;
                for (int nextSubtot = subtot; nextSubtot >= 0;
                                              nextSubtot -= coin)
                    count += apply(nextIndex, nextSubtot);

                memo.put(key, count);
                return count;
            }
        };

        return solve.apply(0, total);
    }

    private static int[] readRecord(final Scanner sc, final int length) {
        final int[] values = new int[length];
        for (int i = 0; i < length; ++i) values[i] = sc.nextInt();
        return values;
    }

    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            final int total = sc.nextInt(), length = sc.nextInt();
            final int[] coins = readRecord(sc, length);
            System.out.println(countWays(coins, total));
        }
    }

    private Solution() {
        throw new AssertionError();
    }
}
