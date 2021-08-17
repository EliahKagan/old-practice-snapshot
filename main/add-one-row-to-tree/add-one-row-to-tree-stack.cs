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
    public TreeNode AddOneRow(TreeNode root, int v, int d) {
        if (d <= 0) throw new ArgumentOutOfRangeException(paramName: nameof(d));
        if (root == null) return null;
        
        root = MakeNode(0, root, null);
        InsertRow(root, d - 1, v);
        return root.left;
    }
    
    private static void InsertRow(TreeNode root, int level, int val) {
        foreach (var node in GetLevel(root, level)) {
            node.left = MakeNode(val, node.left, null);
            node.right = MakeNode(val, null, node.right);
        }
    }
    
    private static IEnumerable<TreeNode> GetLevel(TreeNode root, int level) {
        var stack = new Stack<(TreeNode, int)>();
        stack.Push((root, level));
        
        while (stack.Count != 0) {
            var (subroot, sublevel) = stack.Pop();
            
            if (sublevel > 0) {
                if (subroot.right != null)
                    stack.Push((subroot.right, sublevel - 1));
                if (subroot.left != null)
                    stack.Push((subroot.left, sublevel - 1));
            }
            else yield return subroot;
        }
    }
    
    private static TreeNode MakeNode(int val, TreeNode left, TreeNode right) {
        var node = new TreeNode(val);
        node.left = left;
        node.right = right;
        return node;
    }
}
