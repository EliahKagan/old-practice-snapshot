public class Solution {
    public int ThreeSumClosest(int[] nums, int target) {
        if (nums.Length < 3) throw new ArgumentException(nameof(nums));

        Array.Sort(nums);
        var right_start = nums.Length - 1;
        var left_stop = right_start - 1;
        var best_delta = int.MaxValue; // delta = actual - target
        var best_delta_abs = best_delta;

        for (var left = 0; left != left_stop; ++left) {
            var partial = nums[left] - target;
            var mid = left + 1;
            var right = right_start;

            while (mid < right) {
                var delta = partial + nums[mid] + nums[right];
                if (delta == 0) return target;

                var delta_abs = Math.Abs(delta);
                if (delta_abs < best_delta_abs) {
                    best_delta_abs = delta_abs;
                    best_delta = delta;
                }

                if (delta < 0) ++mid;
                else --right;
            }
        }

        return target + best_delta;
    }
}
