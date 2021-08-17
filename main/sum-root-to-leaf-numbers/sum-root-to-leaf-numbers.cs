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
    public int SumNumbers(TreeNode root) {
        const int radix = 10;

        var sum = 0;
        var cur = 0;

        void Dfs(TreeNode node) {
            if (node == null) return;

            cur = cur * radix + node.val;

            if (node.left != null || node.right != null) {
                Dfs(node.left);
                Dfs(node.right);
            }
            else sum += cur;

            cur /= radix;
        }

        Dfs(root);
        return sum;
    }
}
