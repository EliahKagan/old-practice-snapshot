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
        => root != null && HasPathSumToLeaf(root, sum);

    private static bool HasPathSumToLeaf(TreeNode root, int sum) {
        sum -= root.val;
        if (root.left == null && root.right == null) return sum == 0;

        return root.left != null && HasPathSumToLeaf(root.left, sum)
            || root.right != null && HasPathSumToLeaf(root.right, sum);
    }
}
