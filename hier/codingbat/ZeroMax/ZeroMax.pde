import java.util.StringJoiner;

private static int indexOfMaxOdd(final int[] nums, int start)
{
  int index = nums.length;
  
  for (int max = Integer.MIN_VALUE; start != nums.length; ++start) {
    if (nums[start] % 2 != 0 && max < nums[start]) {
      max = nums[start];
      index = start;
    }
  }
  
  return index;
}

private static int[] zeroMax(final int[] nums) {
  for (int i = 0, j = 0; i != nums.length; ++i) {
    if (nums[i] != 0) continue;
    
    if (j <= i) {
      j = indexOfMaxOdd(nums, i);
      if (j == nums.length) break;
    }
    
    nums[i] = nums[j];
  }
  
  return nums;
}

private static void test(final int... nums) {
  final StringJoiner sj = new StringJoiner(", ", "[", "]");
  for (final int n : zeroMax(nums)) sj.add(String.valueOf(n));
  System.out.println(sj);
}

public static void main(final String[] args) {
  test(0, 5, 0, 3);
  test(0, 4, 0, 3);
  test(0, 1, 0);
}