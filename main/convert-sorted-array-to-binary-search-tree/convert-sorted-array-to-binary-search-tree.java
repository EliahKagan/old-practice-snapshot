/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    public TreeNode sortedArrayToBST(int[] nums) {
        return sortedArrayToBST(nums, 0, nums.length - 1);
    }

    private static TreeNode sortedArrayToBST(final int[] nums,
                                             final int left, final int right) {
        if (left > right) return null;

        final int mid = left + (right - left) / 2;

        return makeNode(nums[mid], sortedArrayToBST(nums, left, mid - 1),
                                   sortedArrayToBST(nums, mid + 1, right));
    }

    private static TreeNode makeNode(final int val, final TreeNode left,
                                                    final TreeNode right) {
        final TreeNode node = new TreeNode(val);
        node.left = left;
        node.right = right;
        return node;
    }
}
