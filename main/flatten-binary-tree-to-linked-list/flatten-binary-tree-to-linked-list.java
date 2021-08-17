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
    public void flatten(TreeNode root) {
        if (root == null) return;

        final Deque<TreeNode> stack = new ArrayDeque<>();
        stack.push(root);

        final TreeNode sentinel = new TreeNode(0);
        TreeNode prev = sentinel;

        while (!stack.isEmpty()) {
            final TreeNode cur = stack.pop();

            if (cur.right != null) {
                stack.push(cur.right);
                cur.right = null;
            }
            if (cur.left != null) {
                stack.push(cur.left);
                cur.left = null;
            }

            prev = prev.right = cur;
        }
    }
}
