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
    public TreeNode AddOneRow(TreeNode root, int v, int d) {
        if (d <= 0) throw new ArgumentOutOfRangeException(paramName: nameof(d));
        if (root == null) return null;
        
        root = MakeNode(0, root, null);
        InsertRow(root, d - 1, v);
        return root.left;
    }
    
    private static void InsertRow(TreeNode root, int level, int val) {
        foreach (var node in GetLevel(root, level)) {
            node.left = MakeNode(val, node.left, null);
            node.right = MakeNode(val, null, node.right);
        }
    }
    
    private static IEnumerable<TreeNode> GetLevel(TreeNode root, int level) {
        var queue = new Queue<TreeNode>();
        queue.Enqueue(root);
        
        while (level-- > 0 && queue.Count != 0) {
            for (var breadth = queue.Count; breadth != 0; --breadth) {
                var node = queue.Dequeue();
                if (node.left != null) queue.Enqueue(node.left);
                if (node.right != null) queue.Enqueue(node.right);
            }
        }
        
        return queue;
    }
    
    private static TreeNode MakeNode(int val, TreeNode left, TreeNode right) {
        var node = new TreeNode(val);
        node.left = left;
        node.right = right;
        return node;
    }
}
