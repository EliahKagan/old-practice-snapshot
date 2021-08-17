private static boolean canBalance(final int[] nums) {
  int right = 0;
  for (final int x : nums) right += x;
  
  if (right == 0) return true; // not strictly needed, since nums is non-empty
  
  int left = 0;
  for (final int x : nums)
    if ((left += x) == (right -= x)) return true;
  
  return false;
}

private static void test(final int... nums) {
  System.out.println(canBalance(nums));
}

public static void main(final String[] args) {
  test(1, 1, 1, 2, 1);
  test(2, 1, 1, 2, 1);
  test(10, 10);
  test(2);
  test();
  test(0);
}