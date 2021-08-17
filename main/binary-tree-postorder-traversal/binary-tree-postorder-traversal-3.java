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
    public List<Integer> postorderTraversal(TreeNode root) {
        final List<Integer> vals = new ArrayList<>();
        final Deque<TreeNode> stack = new ArrayDeque<>();
        TreeNode post = null; // The last node retreated from, if any.

        while (root != null || !stack.isEmpty()) {
            // Go left as far as possible.
            for (; root != null; root = root.left) stack.push(root);

            final TreeNode cur = stack.element();

            if (cur.right != null && cur.right != post) {
                // The right subtree is nonempty and unvisited. Go there.
                root = cur.right;
            } else {
                // The right subtree is explored. Display and retreat.
                post = cur;
                vals.add(post.val);
                stack.pop();
            }
        }

        return vals;
    }
}
