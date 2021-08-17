public class Solution {
    public IList<IList<int>> ThreeSum(int[] nums) {
        var ret = new List<IList<int>>();
        if (nums.Length < 3) return ret;

        Array.Sort(nums);
        var right_start = nums.Length - 1;
        var left_stop = right_start - 1;

        for (var left = 0; left != left_stop; ) {
            var left_elem = nums[left];
            var mid = left + 1;
            var right = right_start;

            while (mid < right) {
                var mid_elem = nums[mid];
                var right_elem = nums[right];
                var total = left_elem + mid_elem + right_elem;

                if (total == 0)
                    ret.Add(new[] { left_elem, mid_elem, right_elem });
                if (total <= 0)
                    while (++mid < right && nums[mid] == mid_elem) { }
                if (total >= 0)
                    while (mid < --right && nums[right] == right_elem) { }
            }

            while (++left != left_stop && nums[left] == left_elem) { }
        }

        return ret;
    }
}
