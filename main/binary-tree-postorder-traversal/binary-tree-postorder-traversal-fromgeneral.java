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
    public List<Integer> postorderTraversal(final TreeNode root) {
        final List<Integer> vals = new ArrayList<>();
        dfs(root, Solution::noop, Solution::noop, vals::add);
        return vals;
    }

    private static void dfs(TreeNode root, final IntConsumer fPre,
                                           final IntConsumer fIn,
                                           final IntConsumer fPost) {
        TreeNode post = null; // The last retreated-from node, if any.
        final Deque<TreeNode> stack = new ArrayDeque<>();

        while (root != null || !stack.isEmpty()) {
            // Go left as far as possible and do the preorder action.
            for (; root != null; root = root.left) {
                fPre.accept(root.val);
                stack.push(root);
            }

            final TreeNode cur = stack.element();

            if (cur.right == null || cur.right != post) {
                // We haven't looked right yet. Do the inorder action.
                fIn.accept(cur.val);
            }

            if (cur.right != null && cur.right != post) {
                // We can traverse right but haven't yet. Do that.
                root = cur.right;
            } else {
                // Do the postorder action and retreat.
                post = cur;
                fPost.accept(post.val);
                stack.pop();
            }
        }
    }

    private static void noop(final int val) { }
}
