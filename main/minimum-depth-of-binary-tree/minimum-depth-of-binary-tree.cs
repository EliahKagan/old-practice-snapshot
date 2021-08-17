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
    public int MinDepth(TreeNode root) {
        if (root == null) return 0;

        var q = new Queue<TreeNode>();
        q.Enqueue(root);

        for (var level = 1; ; ++level) {
            for (var width = q.Count; width != 0; --width) {
                root = q.Dequeue();
                if (root.left == null && root.right == null) return level;
                if (root.left != null) q.Enqueue(root.left);
                if (root.right != null) q.Enqueue(root.right);
            }
        }
    }
}
