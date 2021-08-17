public int[] fix34(int[] nums) {
  int from = 0;
  for (int to = 0; to != nums.length; ++to) {
    if (nums[to] != 3 || nums[to + 1] == 4) continue;

    while (nums[from] != 4 || (from != 0 && nums[from - 1] == 3)) ++from;
    nums[from] = nums[to + 1];
    nums[to + 1] = 4;
  }

  return nums;
}
