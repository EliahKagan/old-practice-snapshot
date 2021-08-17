class Solution {
    public List<List<Integer>> fourSum(int[] nums, int target) {
        final List<List<Integer>> ret = new ArrayList<>();
        if (nums.length < 4) return ret;

        final int gstop = nums.length - 3, hstop = nums.length - 2;
        Arrays.sort(nums);

        for (int g = 0; g != gstop; ) {
            final int gval = nums[g], hij_target = target - gval;

            for (int h = g + 1; h != hstop; ) {
                final int hval = nums[h], ij_target = hij_target - hval;

                for (int i = h + 1, j = nums.length - 1; i < j; ) {
                    final int ival = nums[i], jval = nums[j];
                    final int ij_sum = ival + jval;

                    if (ij_sum == ij_target)
                        ret.add(Arrays.asList(gval, hval, ival, jval));

                    if (ij_sum <= ij_target)
                        while (nums[i] == ival && i < j) ++i;

                    if (ij_sum >= ij_target)
                        while (nums[j] == jval && i < j) --j;
                }

                while (nums[h] == hval && h != hstop) ++h;
            }

            while (nums[g] == gval && g != gstop) ++g;
        }

        return ret;
    }
}
