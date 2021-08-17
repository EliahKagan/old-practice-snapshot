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
        var ls = new Stack<TreeNode>();
        var rs = new Stack<TreeNode>();
        ls.Push(root.left);
        rs.Push(root.right);

        while (ls.Count != 0) {
            var left = ls.Pop();
            var right = rs.Pop();

            if (left == null) {
                if (right != null) return false;
                continue;
            }

            if (right == null || left.val != right.val) return false;

            ls.Push(left.left);
            ls.Push(left.right);
            rs.Push(right.right);
            rs.Push(right.left);
        }

        return true;
    }
}
