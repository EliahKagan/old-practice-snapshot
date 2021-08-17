import java.util.StringJoiner;

private static boolean even(final int[] nums, final int index) {
  return (nums[index] & 1) == 0;
}

private static void swap(final int[] nums, final int i, final int j) {
  final int tmp = nums[i];
  nums[i] = nums[j];
  nums[j] = tmp;
}

private static int[] evenOdd(final int[] nums) {
  for (int i = 0, j = nums.length - 1; i < j; ) {
    if (even(nums, i))      ++i;
    else if (even(nums, j)) swap(nums, i++, j--);
    else                    --j;
  }
  
  return nums;
}

private static void test(final int... nums) {
  final StringJoiner sj = new StringJoiner(", ", "[", "]");
  for (final int n : evenOdd(nums)) sj.add(String.valueOf(n));
  System.out.println(sj);
}

public static void main(final String[] args) {
  test(1, 0, 1, 0, 0, 1, 1);
  test(3, 3, 2);
  test(2, 2, 2);
  test(1, 2, 3, 4, 5, 6, 7, 8,  9, 10, -3, -5, -8, -1, -6, 11, 54, 2, 5, 4, 3, 0, 0);
  test();
  test(3);
  test(0);
}