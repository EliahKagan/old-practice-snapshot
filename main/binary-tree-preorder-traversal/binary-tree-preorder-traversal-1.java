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
        if (root == null) return vals;

        final Deque<TreeNode> stack = new ArrayDeque<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            root = stack.pop();
            vals.add(root.val);

            if (root.right != null) stack.push(root.right);
            if (root.left != null) stack.push(root.left);
        }

        return vals;
    }
}
