public int countClumps(int[] nums) {
  if (nums.length == 0) return 0;

  int best = 0, cur = 0;
  int oldval = nums[0];

  for (int val : nums) {
    if (oldval == val) {
      ++cur;
    } else {
      best = Math.max(best, cur);
      cur = 1;
      oldval = val;
    }
  }

  return Math.max(best, cur);
}
