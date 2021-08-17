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
    public TreeNode deleteNode(final TreeNode root, final int key) {
        if (root == null) return null;

        if (key != root.val) {
            if (key < root.val)
                root.left = deleteNode(root.left, key);
            else
                root.right = deleteNode(root.right, key);

            return root;
        }

        if (root.left == null) return root.right;
        if (root.right == null) return root.left;

        final TreeNode node = extractNextBelow(root);
        reparent(root, node);
        return node;
    }

    private static TreeNode extractNextBelow(final TreeNode root) {
        TreeNode node = root.right;

        if (node.left == null) {
            root.right = node.right;
        } else {
            while (node.left.left != null) node = node.left;
            final TreeNode parent = node;
            node = node.left;
            parent.left = node.right;
        }

        node.right = null; // makes debugging easier
        return node;
    }

    private static void reparent(final TreeNode oldParent,
                                 final TreeNode newParent) {
        newParent.left = oldParent.left;
        newParent.right = oldParent.right;

        oldParent.left = oldParent.right = null; // makes debugging easier
    }
}
