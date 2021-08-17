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
