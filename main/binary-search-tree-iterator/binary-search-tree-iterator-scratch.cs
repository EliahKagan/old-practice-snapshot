using System;
using System.Collections.Generic;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

public sealed class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;
    public TreeNode(int x) { val = x; }

    internal TreeNode(int x, TreeNode lsub, TreeNode rsub)
    { // for debugging
        val = x;
        left = lsub;
        right = rsub;
    }
}

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

internal static class UnitTest {
    private static void Main() {
        var lsub = new TreeNode(20, new TreeNode(30), new TreeNode(40));
        var rsub = new TreeNode(50, new TreeNode(60, null, new TreeNode(70)), new TreeNode(80));
        var root = new TreeNode(10, lsub, rsub);

        var it = new BSTIterator(root);
        while (it.HasNext()) Console.WriteLine(it.Next());
    }
}
