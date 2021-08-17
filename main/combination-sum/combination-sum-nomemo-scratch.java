import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public List<List<Integer>> combinationSum(final int[] candidates,
                                              final int target) {
        final int len = candidates.length;
        final int[] counts = new int[len];
        final List<List<Integer>> ret = new ArrayList<>();

        final class Helper {
            private void dfs(int index, int subtot) {
                if (subtot == 0) {
                    ret.add(canonicalize(index));
                    return;
                }

                if (index == len) return;

                for (final int value = candidates[index]; subtot >= 0;
                                                          subtot -= value) {
                    dfs(index + 1, subtot);
                    ++counts[index];
                }

                counts[index] = 0;
            }

            private List<Integer> canonicalize(final int stop) {
                final List<Integer> ret = new ArrayList<>();

                for (int i = 0; i != stop; ++i) {
                    final Integer value = candidates[i];
                    for (int c = counts[i]; c != 0; --c) ret.add(value);
                }

                return ret;
            }

        }

        new Helper().dfs(0, target);
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
