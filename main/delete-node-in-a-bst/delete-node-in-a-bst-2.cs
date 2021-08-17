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
    public TreeNode DeleteNode(TreeNode root, int key) {
        if (root == null) return null;

        if (key < root.val) {
            root.left = DeleteNode(root.left, key);
            return root;
        }

        if (root.val < key) {
            root.right = DeleteNode(root.right, key);
            return root;
        }

        // If it has at most than one child just replace it with that (or null).
        if (root.right == null) return root.left;
        if (root.left == null) return root.right;

        // If its right child has no left child, attach its left child as the
        // left chld of its right child.
        if (root.right.left == null) {
            root.right.left = root.left;
            return root.right;
        }

        // Find the minimal node in its right subtree.
        var parent = root.right;
        var child = parent.left;
        while (child.left != null) {
            parent = child;
            child = child.left;
        }

        // Replace it with that minimal node. Very carefully.
        parent.left = child.right;
        child.right = root.right;
        child.left = root.left;
        return child;
    }
}
