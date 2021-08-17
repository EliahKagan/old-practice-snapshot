public int maxSpan(int[] nums) { // Amortized O(nums.length) w.h.p way, for fun.
  Map<Integer, int[]> spans = new HashMap<>();

  for (int i = 0; i != nums.length; ++i) {
    final int i_ = i;
    int[] span = spans.computeIfAbsent(nums[i], (key -> new int[] { i_, i_ }));
    span[1] = i;
  }

  int acc = -1;
  for (int[] span : spans.values()) acc = Math.max(acc, span[1] - span[0]);
  return acc + 1;
}
