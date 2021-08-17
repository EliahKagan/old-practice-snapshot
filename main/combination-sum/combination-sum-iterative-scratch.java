import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public List<List<Integer>>
    combinationSum(final int[] candidates, int target) {
        final int len = candidates.length;
        final int[] counts = new int[len];
        final List<List<Integer>> ret = new ArrayList<>();

        for (int j = -1; ; ) {
            // advance
            if (target == 0) ret.add(canonicalize(candidates, counts, ++j));
            else j = len;

            // retreat
            for (; ; ) {
                if (j-- == 0) return ret;

                ++counts[j];
                target -= candidates[j];
                if (target >= 0) break;

                target += candidates[j] * counts[j];
                counts[j] = 0;
            }
        }
    }

    private static List<Integer>
    canonicalize(final int[] candidates, final int[] counts, final int stop) {
        final List<Integer> ret = new ArrayList<>();

        for (int i = 0; i != stop; ++i) {
            final Integer value = candidates[i];
            for (int c = counts[i]; c != 0; --c) ret.add(value);
        }

        return ret;
    }
}

final class UnitTest {
    public static void main(final String[] args) {
        test(new int[] { 2, 3, 6, 7 }, 7);
        test(new int[] { 1, 2, 3, 4, 5 }, 22);
    }

    private static void test(final int[] candidates, final int target) {
        System.out.format("%ncombinationSum(%s, %d):%n",
                          Arrays.toString(candidates), target);

        new Solution().combinationSum(candidates, target)
                      .forEach(ways -> System.out.println("\t" + ways));
    }

    private UnitTest() { throw new AssertionError(); }
}
