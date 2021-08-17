import java.util.StringJoiner;

private static void swap(final int[] nums, final int i, final int j) {
  final int tmp = nums[i];
  nums[i] = nums[j];
  nums[j] = tmp;
}

private static int[] fix34(final int[] nums) {
  for (int i = 0, j = 1; i != nums.length; ) {
    if (nums[i++] == 3 && nums[i] != 4) {
      while (nums[j] != 4 || nums[j - 1] == 3) ++j;
      swap(nums, i, j);
    }
  }
  
  return nums;
}

private static void test(final int... nums) {
  final StringJoiner sj = new StringJoiner(", ", "[", "]");
  for (final int n : fix34(nums)) sj.add(String.valueOf(n));
  System.out.println(sj);
}

public static void main(final String[] args) {
  test(1, 3, 1, 4);
  test(1, 3, 1, 4, 4, 3, 1);
  test(3, 2, 2, 4);
  test(4);
  test(9);
  test(10, 20);
  test();
}