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
        final Deque<TreeNode> path = new ArrayDeque<>();
        final Deque<Boolean> vis = new ArrayDeque<>();

        final Consumer<TreeNode> goLeft = node -> {
            for (; node != null; node = node.left) {
                path.push(node);
                vis.push(Boolean.FALSE);
            }
        };

        final List<Integer> ret = new ArrayList<>();

        for (goLeft.accept(root); !path.isEmpty(); ) {
            if (vis.pop()) {
                ret.add(path.pop().val);
            } else {
                vis.push(Boolean.TRUE);
                goLeft.accept(path.element().right);
            }
        }

        return ret;
    }
}
