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
    public List<Integer> preorderTraversal(final TreeNode root) {
        final List<Integer> vals = new ArrayList<>();
        dfs(vals, root);
        return vals;
    }

    private static void dfs(final List<Integer> vals, final TreeNode root) {
        if (root != null) {
            vals.add(root.val);
            dfs(vals, root.left);
            dfs(vals, root.right);
        }
    }
}
