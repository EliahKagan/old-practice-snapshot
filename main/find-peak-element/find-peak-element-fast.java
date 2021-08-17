class Solution {
    public int findPeakElement(final int[] nums) {
        for (int low = 0, high = nums.length - 1; low <= high; ) {
            final int mid = low + (high - low) / 2;

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
}
