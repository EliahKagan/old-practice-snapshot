<Query Kind="Program" />

public class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;
    public TreeNode(int x) { val = x; }
    
    internal TreeNode(int x, TreeNode lsub, TreeNode rsub) { // for debugging
        val = x;
        left = lsub;
        right = rsub;
    }
}

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

    public IList<int> PreorderTraversal(TreeNode root) {
        var path = new List<int>();
        if (root == null) return path;
        
        var stack = new Stack<TreeNode>();
        for (stack.Push(root); stack.Count != 0; ) {
            root = stack.Pop();
            path.Add(root.val);
            if (root.right != null) stack.Push(root.right);
            if (root.left != null) stack.Push(root.left);
        }
        
        return path;
    }
    
    // A recursive preorder traversal implementation, for testing.
    internal IList<int> PreorderTraversalRecursive(TreeNode root) {
        var path = new List<int>();
        
        void Dfs(TreeNode node) {
            if (node != null) {
                path.Add(node.val);
                Dfs(node.left);
                Dfs(node.right);
            }
        }
        
        Dfs(root);
        return path;
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
    
    // A recursive postorder traversal implementation, for testing.
    internal IList<int> PostorderTraversalRecursive(TreeNode root) {
        var path = new List<int>();
        
        void Dfs(TreeNode node) {
            if (node != null) {
                Dfs(node.left);
                Dfs(node.right);
                path.Add(node.val);
            }
        }
        
        Dfs(root);
        return path;
    }
    
    public IList<int> InorderTraversal(TreeNode root) {
        var path = new List<int>();
        if (root == null) return path;
        
        var stack = new Stack<State>();
        stack.Push(new State(root, Step.GoLeft));
        
        while (stack.Count != 0) {
            var state = stack.Peek();
            
            switch (state.Next) {
            case Step.GoLeft:
                state.Next = Step.Display;
                var left = state.Node.left;
                if (left != null) stack.Push(new State(left, Step.GoLeft));
                break;
            
            case Step.Display:
                state.Next = Step.GoRight;
                path.Add(state.Node.val);
                break;
            
            case Step.GoRight:
                stack.Pop();
                var right = state.Node.right;
                if (right != null) stack.Push(new State(right, Step.GoLeft));
                break;
            }
        }
        
        return path;
    }
    
    // A recursive inorder traversal implementation, for testing.
    internal IList<int> InorderTraversalRecursive(TreeNode root) {
        var path = new List<int>();
        
        void Dfs(TreeNode node) {
            if (node != null) {
                Dfs(node.left);
                path.Add(node.val);
                Dfs(node.right);
            }
        }
        
        Dfs(root);
        return path;
    }
}

private static void Main() {
    var lsub = new TreeNode(20, new TreeNode(30), new TreeNode(40));
    var rsub = new TreeNode(50, new TreeNode(60, null, new TreeNode(70)), new TreeNode(80));
    var root = new TreeNode(10, lsub, rsub).Dump("The tree.");
    
    var s = new Solution();
    s.PreorderTraversal(root).Dump("The preorder traversal (by iteration).");
    s.PreorderTraversalRecursive(root).Dump("The preorder traversal (by recursion).");
    s.PostorderTraversal(root).Dump("The postorder traversal (by iteration).");
    s.PostorderTraversalRecursive(root).Dump("The postorder traversal (by recursion).");
    s.InorderTraversal(root).Dump("The inorder traversal (by iteration).");
    s.InorderTraversalRecursive(root).Dump("The inorder traversal (by recursion).");
}