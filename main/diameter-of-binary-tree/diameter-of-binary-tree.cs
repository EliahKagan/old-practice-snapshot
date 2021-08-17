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
    public int DiameterOfBinaryTree(TreeNode root) {
        var (_, d) = HeightAndDiameter(root);
        return d;
    }
    
    private static (int, int) HeightAndDiameter(TreeNode root) {
        if (root == null) return (0, 0);
        
        var (lh, ld) = HeightAndDiameter(root.left);
        var (rh, rd) = HeightAndDiameter(root.right);
        
        var h = Math.Max(lh, rh) + 1;
        var d = Math.Max(Math.Max(ld, rd), lh + rh);
        return (h, d);
    }
}
