public int countClumps(int[] nums) {
  if (nums.length == 0) return 0;

  int count = 0, length = 0;
  int oldval = nums[0];

  for (int val : nums) {
    if (oldval == val) {
      ++length;
    } else {
      if (length > 1) ++count;
      length = 1;
      oldval = val;
    }
  }

  if (length > 1) ++count;
  return count;
}
