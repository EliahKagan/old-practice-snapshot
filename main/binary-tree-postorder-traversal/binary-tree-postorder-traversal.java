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
        class State {
            State(final TreeNode node) { this.node = node; }
            final TreeNode node;
            boolean retreated = false;
        }

        final Deque<State> stack = new ArrayDeque<>();

        final Consumer<TreeNode> goLeft = node -> {
            for (; node != null; node = node.left) stack.push(new State(node));
        };

        final List<Integer> ret = new ArrayList<>();

        for (goLeft.accept(root); !stack.isEmpty(); ) {
            final State state = stack.element();

            if (state.retreated) {
                ret.add(state.node.val);
                stack.pop();
            } else {
                state.retreated = true;
                goLeft.accept(state.node.right);
            }
        }

        return ret;
    }
}
