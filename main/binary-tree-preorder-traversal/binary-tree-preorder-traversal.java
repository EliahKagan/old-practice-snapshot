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
        final Deque<TreeNode> stack = new ArrayDeque<>();

        while (root != null || !stack.isEmpty()) {
            // Go left as far as possible.
            for (; root != null; root = root.left) {
                vals.add(root.val);
                stack.push(root);
            }

            // Go right.
            root = stack.pop().right;
        }

        return vals;
    }
}
