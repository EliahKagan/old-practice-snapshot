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

    private enum Action { GO_LEFT, GO_RIGHT, RETREAT }

    private static class Frame {
        Frame(final TreeNode node) {
            this.node = node;
            this.action = Action.GO_LEFT;
        }

        final TreeNode node;
        Action action;
    }

    private static void dfs(TreeNode root, final IntConsumer fPre,
                                           final IntConsumer fIn,
                                           final IntConsumer fPost) {
        if (root == null) return;
        final Deque<Frame> stack = new ArrayDeque<>();
        stack.push(new Frame(root));

        while (!stack.isEmpty()) {
            final Frame frame = stack.element();

            switch (frame.action) {
                case GO_LEFT:
                    fPre.accept(frame.node.val);
                    if (frame.node.left != null)
                        stack.push(new Frame(frame.node.left));
                    frame.action = Action.GO_RIGHT;
                    break;

                case GO_RIGHT:
                    fIn.accept(frame.node.val);
                    if (frame.node.right != null)
                        stack.push(new Frame(frame.node.right));
                    frame.action = Action.RETREAT;
                    break;

                case RETREAT:
                    fPost.accept(frame.node.val);
                    stack.pop();
                    break;

                default:
                    throw new IllegalStateException("unrecognized DFS phase");
            }
        }
    }

    private static void noop(final int val) { }
}
