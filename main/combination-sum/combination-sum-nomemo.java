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
