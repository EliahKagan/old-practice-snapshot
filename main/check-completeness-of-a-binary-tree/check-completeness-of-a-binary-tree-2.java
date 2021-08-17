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
    public boolean isCompleteTree(final TreeNode root) {
        if (root == null) return true;
        
        boolean gotLeaf = false;
        final Queue<TreeNode> nodes = new ArrayDeque<>();
        
        for (nodes.add(root); !nodes.isEmpty(); ) {
            final TreeNode node = nodes.remove();
            
            if (node.left == null)
                gotLeaf = true;
            else if (gotLeaf)
                return false;
            else
                nodes.add(node.left);
            
            if (node.right == null)
                gotLeaf = true;
            else if (gotLeaf)
                return false;
            else
                nodes.add(node.right);
        }
        
        return true;
    }
}
