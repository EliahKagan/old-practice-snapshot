private static int countClumps(final int[] nums) {
  int clump_count = 0;
  
  for (int i = 0; i != nums.length; ) {
    int clump_size = 0;
    
    for (final int x = nums[i]; i != nums.length && nums[i] == x; ++i)
      ++clump_size;
    
    if (clump_size != 1) ++clump_count;
  }
  
  return clump_count;
}


private static void test(final int... nums) {
  System.out.println(countClumps(nums));
}

public static void main(final String[] args) {
  test(1, 2, 2, 3, 4, 4);
  test(1, 1, 2, 1, 1);
  test(1, 1, 1, 1, 1);
}