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
        if (level > 0) {
            if (root.left != null) InsertRow(root.left, level - 1, val);
            if (root.right != null) InsertRow(root.right, level - 1, val);
        } else {
            root.left = MakeNode(val, root.left, null);
            root.right = MakeNode(val, null, root.right);
        }
    }
    
    private static TreeNode MakeNode(int val, TreeNode left, TreeNode right) {
        var node = new TreeNode(val);
        node.left = left;
        node.right = right;
        return node;
    }
}
