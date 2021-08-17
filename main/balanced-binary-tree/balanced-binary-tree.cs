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
    public bool IsBalanced(TreeNode root) {
        const int unbalanced = -1;

        int BalancedDepth(TreeNode node) {
            if (node == null) return 0;

            var left = BalancedDepth(node.left);
            if (left == unbalanced) return unbalanced;

            var right = BalancedDepth(node.right);
            if (right == unbalanced) return unbalanced;

            return Math.Abs(left - right) > 1
                    ? unbalanced
                    : Math.Max(left, right) + 1;
        }

        return BalancedDepth(root) != unbalanced;
    }
}
