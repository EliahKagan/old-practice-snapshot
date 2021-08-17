public class Solution {
    public bool CanJump(int[] nums) {
        var istop = nums.Length;
        var reach = new bool[istop];
        reach[0] = true;

        for (var i = 0; i != istop; ++i) {
            if (reach[i]) {
                var jstop = Math.Min(istop, i + nums[i] + 1);
                for (var j = i + 1; j != jstop; ++j) reach[j] = true;
            }
        }

        return reach[istop - 1];
    }
}
