final class Solution {
    public static void main(final String[] args) {
        var nums = new int[1_065_000_000];
        for (var i = 1; i <= 831_522_714; ++i)
            nums[i] = nums[i - 1] + 1;
        for (var i = 831_522_715; i < nums.length; ++i)
            nums[i] = nums[i - 1] - 1;

        var ans = findPeakElement(nums);
        System.out.format("Answer is index %d, value %d.%n", ans, nums[ans]);
    }

    private static int findPeakElement(final int[] nums) {
        int cycles = 0;

        for (int low = 0, high = nums.length - 1; low <= high; ) {
            final int mid = low + (high - low) / 2;
            System.err.format("at nums[%d] = %d\t(cycle %d)%n",
                              mid, nums[mid], ++cycles);

            if (mid != 0 && nums[mid - 1] > nums[mid]) {
                high = mid - 1;
            } else if (mid != nums.length - 1 && nums[mid + 1] > nums[mid]) {
                low = mid + 1;
            } else {
                return mid;
            }
        }

        throw new IllegalArgumentException("array does not have peak element");
    }

    private Solution() { throw new AssertionError(); }
}
