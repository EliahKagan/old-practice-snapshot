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
    public TreeNode trimBST(final TreeNode root, final int L, final int R) {
        return trimLeft(trimRight(root, R), L);
    }
    
    private static TreeNode trimLeft(final TreeNode root, final int L) {
        if (root == null) return null;
        
        if (root.val < L) return trimLeft(root.right, L);
        
        root.left = trimLeft(root.left, L);
        return root;
    }
    
    private static TreeNode trimRight(final TreeNode root, final int R) {
        if (root == null) return null;
        
        if (root.val > R) return trimRight(root.left, R);
        
        root.right = trimRight(root.right, R);
        return root;
    }
}
