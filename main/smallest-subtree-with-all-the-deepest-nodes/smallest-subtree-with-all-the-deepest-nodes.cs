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
    public TreeNode SubtreeWithAllDeepest(TreeNode root) {
        var (_, b) = HeightAndBestRoot(root);
        return b;
    }
    
    private static (int, TreeNode) HeightAndBestRoot(TreeNode root) {
        if (root == null) return (0, null);
        
        var (lh, lb) = HeightAndBestRoot(root.left);
        var (rh, rb) = HeightAndBestRoot(root.right);
        
        if (lh > rh) return (lh + 1, lb);
        if (lh < rh) return (rh + 1, rb);
        return (lh + 1, root);
    }
}
