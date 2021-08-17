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
    public bool IsSymmetric(TreeNode root) {
        if (root == null) return true;

        var stack = new Stack<(TreeNode, TreeNode)>();
        stack.Push((root.left, root.right));

        while (stack.Count != 0) {
            var (left, right) = stack.Pop();

            if (left == null || right == null) {
                if (left != null || right != null) return false;
            } else {
                if (left.val != right.val) return false;
                stack.Push((left.right, right.left));
                stack.Push((left.left, right.right));
            }
        }

        return true;
    }
}
