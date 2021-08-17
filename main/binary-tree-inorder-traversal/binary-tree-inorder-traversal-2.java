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
    public List<Integer> inorderTraversal(TreeNode root) {
        final List<Integer> vals = new ArrayList<>();
        final Deque<TreeNode> stack = new ArrayDeque<>();

        while (root != null || !stack.isEmpty()) {
            // Go left as far as possible.
            for (; root != null; root = root.left) stack.push(root);

            // Display the node.
            final TreeNode cur = stack.pop();
            vals.add(cur.val);

            // Go right.
            root = cur.right;
        }

        return vals;
    }
}
