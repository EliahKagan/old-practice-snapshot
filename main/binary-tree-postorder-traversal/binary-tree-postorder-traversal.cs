/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left;
 *     public TreeNode right;
 *     public TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    private enum Step {
        Display,
        GoLeft,
        GoRight,
    }

    private class State {
        public readonly TreeNode Node;
        public Step Next;

        public State(TreeNode node, Step next) {
            Node = node;
            Next = next;
        }
    }

    public IList<int> PostorderTraversal(TreeNode root) {
        var path = new List<int>();
        if (root == null) return path;

        var stack = new Stack<State>();
        stack.Push(new State(root, Step.GoLeft));

        while (stack.Count != 0) {
            var state = stack.Peek();

            switch (state.Next) {
            case Step.GoLeft:
                state.Next = Step.GoRight;
                var left = state.Node.left;
                if (left != null) stack.Push(new State(left, Step.GoLeft));
                break;

            case Step.GoRight:
                state.Next = Step.Display;
                var right = state.Node.right;
                if (right != null) stack.Push(new State(right, Step.GoLeft));
                break;

            case Step.Display:
                path.Add(state.Node.val);
                stack.Pop();
                break;
            }
        }

        return path;
    }
}
