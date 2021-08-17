/**
 * Definition for binary tree
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left;
 *     public TreeNode right;
 *     public TreeNode(int x) { val = x; }
 * }
 */

public sealed class BSTIterator {
    private class State {
        public readonly TreeNode Node;
        public bool TraversedLeft = false;

        public State(TreeNode node) => Node = node;
    }

    public BSTIterator(TreeNode root) {
        if (root != null) _stack.Push(new State(root));
    }

    /** @return whether we have a next smallest number */
    public bool HasNext() => _stack.Count != 0;

    /** @return the next smallest number */
    public int Next() {
        while (_stack.Count != 0) {
            var state = _stack.Peek();

            if (state.TraversedLeft) {
                var ret = state.Node.val;
                _stack.Pop();
                var right = state.Node.right;
                if (right != null) _stack.Push(new State(right));
                return ret;
            } else {
                state.TraversedLeft = true;
                var left = state.Node.left;
                if (left != null) _stack.Push(new State(left));
            }
        }

        throw new InvalidOperationException("can't move past the end");
    }

    private Stack<State> _stack = new Stack<State>();
}

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = new BSTIterator(root);
 * while (i.HasNext()) v[f()] = i.Next();
 */
