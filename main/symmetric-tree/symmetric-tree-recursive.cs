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
    private static bool AreMirrored(TreeNode left, TreeNode right) {
        if (left == null) return right == null;

        if (right == null) return false;

        return left.val == right.val && AreMirrored(left.right, right.left)
                                     && AreMirrored(left.left, right.right);
    }

    public bool IsSymmetric(TreeNode root)
        => root == null || AreMirrored(root.left, root.right);
}
