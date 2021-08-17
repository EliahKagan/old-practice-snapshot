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
    public boolean isCompleteTree(TreeNode root) {
        final TreeNode sentinel = new TreeNode(0);
        
        final Queue<TreeNode> nodes = new ArrayDeque<>();
        nodes.add(root == null ? sentinel : root);
        
        while ((root = nodes.remove()) != sentinel) {
            nodes.add(root.left == null ? sentinel : root.left);
            nodes.add(root.right == null ? sentinel : root.right);
        }
        
        while (!nodes.isEmpty())
            if (nodes.remove() != sentinel) return false;
        
        return true;
    }
}
