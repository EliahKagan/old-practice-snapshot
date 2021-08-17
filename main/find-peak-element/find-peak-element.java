class Solution {
    public int findPeakElement(int[] nums) {
        if (nums.length == 0)
            throw new IllegalArgumentException("empty array has no peak");

        if (nums.length == 1 || nums[0] > nums[1]) return 0;

        final int last = nums.length - 1;
        for (int i = 1; i != last; ++i)
            if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) return i;

        if (nums[last] > nums[last - 1]) return last;
        throw new IllegalArgumentException("no peak found");
    }
}
