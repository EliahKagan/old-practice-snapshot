public class Solution {
    public void Merge(int[] nums1, int m, int[] nums2, int n) {
        var dest = m + n - 1;
        var src1 = m - 1;
        var src2 = n - 1;

        while (0 <= src1 && 0 <= src2) {
            nums1[dest--] = (nums1[src1] > nums2[src2] ? nums1[src1--]
                                                       : nums2[src2--]);
        }

        while (0 <= src1) nums1[dest--] = nums1[src1--];
        while (0 <= src2) nums1[dest--] = nums2[src2--];

        // Neither Debug.Assert nor Contract.Assert works on leetcode.com.
        if (dest != -1) throw new ArgumentOutOfRangeException();
    }
}
