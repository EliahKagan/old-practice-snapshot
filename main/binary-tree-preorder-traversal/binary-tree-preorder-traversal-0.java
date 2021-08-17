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
    public List<Integer> preorderTraversal(TreeNode root) {
        final List<Integer> vals = new ArrayList<>();

        final Consumer<TreeNode> dfs = new Consumer<TreeNode>() {
            @Override
            public void accept(final TreeNode node) {
                if (node == null) return;

                vals.add(node.val);
                accept(node.left);
                accept(node.right);
            }
        };

        dfs.accept(root);
        return vals;
    }
}
