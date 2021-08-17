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
    public TreeNode convertBST(TreeNode root) {
        dfs(root, 0);
        return root;
    }
    
    private static int dfs(TreeNode root, int sum) {
        if (root == null) return sum;
        
        root.val += dfs(root.right, sum);
        return dfs(root.left, root.val);
    }
}
