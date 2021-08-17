private static int maxMirror(final int[] nums, int left, int right) {
  int acc = 0;
  
  while (left != nums.length && right >= 0 && nums[left++] == nums[right--])
    ++acc;
  
  return acc;
}

private static int maxMirror(final int[] nums) {
  int acc = 0;
  
  for (int left = 0; left != nums.length; ++left) {
    for (int right = nums.length - 1; left <= right; --right)
      acc = Math.max(acc, maxMirror(nums, left, right));
  }
  
  return acc;
}

private static void test(final int... nums) {
  System.out.println(maxMirror(nums));
}

public static void main(final String[] args) {
  test(1, 2, 3, 8, 9, 3, 2, 1);
  test(1, 2, 1, 4);
  test(7, 1, 2, 9, 7, 2, 1);
  test(10, 20, 10, 20);
  test();
  test(3);
}