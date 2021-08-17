class Solution {
    public int fourSumCount(final int[] a, final int[] b,
                            final int[] c, final int[] d)
    {
        Arrays.sort(c);
        Arrays.sort(d);

        int count = 0;
        for (final int aval : a)
            for (final int bval : b) count += twoSumCount(c, d, -aval - bval);

        return count;
    }

    /** Helper function for fourSumCount. xs and ys must be sorted. */
    private static int twoSumCount(final int[] xs, final int[] ys,
                                   final int target)
    {
        int count = 0;

        final int istop = xs.length, jstop = -1;
        for (int i = 0, j = ys.length - 1; i != istop && j != jstop; ) {
            final int x = xs[i], y = ys[j], sum = x + y;

            if (sum == target) {
                int di = 1, dj = 1;
                while (++i != istop && xs[i] == x) ++di;
                while (--j != jstop && ys[j] == y) ++dj;
                count += di * dj;
            }
            else if (sum < target) ++i;
            else --j;
        }

        return count;
    }
}
