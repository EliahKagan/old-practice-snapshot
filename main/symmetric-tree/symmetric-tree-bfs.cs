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

        var queue = new Queue<(TreeNode, TreeNode)>();
        queue.Enqueue((root.left, root.right));

        while (queue.Count != 0) {
            var (left, right) = queue.Dequeue();

            if (left == null || right == null) {
                if (left != null || right != null) return false;
            }
            else if (left.val != right.val) return false;
            else {
                queue.Enqueue((left.left, right.right));
                queue.Enqueue((left.right, right.left));
            }
        }

        return true;
    }
}
