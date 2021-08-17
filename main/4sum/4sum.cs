public class Solution {
    public IList<IList<int>> FourSum(int[] nums, int target) {
        var ret = new List<IList<int>>();
        if (nums.Length < 4) return ret;

        Array.Sort(nums);

        var kstart = nums.Length - 1;
        var istop = kstart - 1;
        var hstop = istop - 1;

        for (var h = 0; h != hstop; ) {
            var hval = nums[h];
            var outer_partial = hval - target;

            for (var i = h + 1; i != istop; ) {
                var ival = nums[i];
                var inner_partial = outer_partial + ival;

                var j = i + 1;
                var k = kstart;

                while (j < k) {
                    var jval = nums[j];
                    var kval = nums[k];
                    var total = inner_partial + jval + kval;

                    if (total == 0)
                        ret.Add(new[] { hval, ival, jval, kval });
                    if (total <= 0)
                        while (++j < k && nums[j] == jval) { }
                    if (total >= 0)
                        while (j < --k && nums[k] == kval) { }
                }

                while (++i != istop && nums[i] == ival) { }
            }

            while (++h != hstop && nums[h] == hval) { }
        }

        return ret;
    }
}
