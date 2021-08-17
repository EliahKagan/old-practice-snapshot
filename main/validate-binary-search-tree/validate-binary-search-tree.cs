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
    private static bool IsValidBST(TreeNode root, int? min, int? max)
        => root == null ||
            (!(root.val <= min || root.val >= max)      // values are in range
             && IsValidBST(root.left, min, root.val)    // left subtree is BST
             && IsValidBST(root.right, root.val, max)); // right subtree is BST

    public bool IsValidBST(TreeNode root) => IsValidBST(root, null, null);
}
