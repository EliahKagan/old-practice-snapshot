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
        if (root == null) yield break;
        
        if (level > 0) {
            var lefts = GetLevel(root.left, level - 1);
            var rights = GetLevel(root.right, level - 1);
            foreach (var node in lefts.Concat(rights)) yield return node;
        }
        else yield return root;
    }
    
    private static TreeNode MakeNode(int val, TreeNode left, TreeNode right) {
        var node = new TreeNode(val);
        node.left = left;
        node.right = right;
        return node;
    }
}
