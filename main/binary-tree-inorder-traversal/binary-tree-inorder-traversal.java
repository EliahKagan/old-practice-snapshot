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
        final List<Integer> ret = new ArrayList<>();
        final Deque<TreeNode> stack = new ArrayDeque<>();

        for (; ; ) {
            for (; root != null; root = root.left) stack.push(root);

            if (stack.isEmpty()) break;

            root = stack.pop();
            ret.add(root.val);
            root = root.right;
        }

        return ret;
    }
}
