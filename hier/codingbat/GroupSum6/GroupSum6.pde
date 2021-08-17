private static boolean groupSum6Wrapper(final int start, final int[] nums,
                                        final int target) {
  System.out.format("Calling groupSum6 with start=%d, target=%d.%n",
                    start, target);
  
  final boolean ret = groupSum6(start, nums, target);
  
  System.out.format("Result of groupSum6 with start=%d, target=%d is %b.%n",
                    start, target, ret);
  return ret;
}

private static boolean groupSum6(final int start, final int[] nums,
                                 final int target) {
  if (start == nums.length) return target == 0;
  
  return groupSum6Wrapper(start + 1, nums, target - nums[start])
          || (nums[start] != 6 && groupSum6Wrapper(start + 1, nums, target));
}

public static void main(final String[] args) {
  groupSum6Wrapper(0, new int[] { 5, 2, 4, 6 }, 9);
}