<Query Kind="Program" />

public class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;
    public TreeNode(int x) { val = x; }
}

public class Solution {
    public int KthSmallest(TreeNode root, int k)
        => Inorder(root).ElementAt(k - 1);
    
    private static IEnumerable<int> Inorder(TreeNode root) {
        var stack = new Stack<TreeNode>();
        
        bool GoLeft() {
            for (; root != null; root = root.left) stack.Push(root);
            return stack.Count != 0;
        }
        
        for (; GoLeft(); root = root.right) {
            root = stack.Pop();
            yield return root.val;
        }
    }
}

private static void Main() { }
