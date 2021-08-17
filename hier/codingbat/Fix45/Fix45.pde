import java.util.StringJoiner;

private static void swap(final int[] nums, final int i, final int j) {
  final int tmp = nums[i];
  nums[i] = nums[j];
  nums[j] = tmp;
}

private static int[] fix45(final int[] nums) {
  for (int i = 0, j = 0; i != nums.length; ) {
    if (nums[i++] == 4 && nums[i] != 5) {
      while (nums[j] != 5 || (j != 0 && nums[j - 1] == 4)) ++j;
      swap(nums, i, j);
    }
  }
  
  return nums;
}

private static void test(final int... nums) {
  final StringJoiner sj = new StringJoiner(", ", "[", "]");
  for (final int n : fix45(nums)) sj.add(String.valueOf(n));
  System.out.println(sj);
}

public static void main(final String[] args) {
  test(5, 4, 9, 4, 9, 5);
  test(1, 4, 1, 5);
  test(1, 4, 1, 5, 5, 4, 1);
  test(5, 5, 5, 4, 4, 3); // though the problem constrains don't allow this
  test(3);
  test(10, 20);
  test();
}