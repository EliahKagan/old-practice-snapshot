class Solution {
    private static final Integer ZERO = Integer.valueOf(0);

    public int fourSumCount(final int[] a, final int[] b,
                            final int[] c, final int[] d)
    {
        final Map<Integer, Integer> ab_sums = new HashMap<>();
        for (final int w : a) {
            for (final int x : b) {
                final Integer sum = w + x;
                ab_sums.put(sum, ab_sums.getOrDefault(sum, ZERO) + 1);
            }
        }

        int count = 0;
        for (final int x : c) {
            for (final int y : d)
                count += ab_sums.getOrDefault(-(x + y), ZERO);
        }

        return count;
    }
}
