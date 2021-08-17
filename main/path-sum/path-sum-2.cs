/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left;
 *     public TreeNode right;
 *     public TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public bool HasPathSum(TreeNode root, int sum)
        => root != null && ((root.left == null && root.right == null
                                               && root.val == sum)
                            || HasPathSum(root.left, sum - root.val)
                            || HasPathSum(root.right, sum - root.val));
}
