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
    public IList<int> InorderTraversal(TreeNode root) {
        var ret = new List<int>();
        var stack = new Stack<TreeNode>();
        
        while (root != null || stack.Count != 0) {
            // Go left as far as possible.
            for (; root != null; root = root.left) stack.Push(root);
            
            // Process the current node.
            var cur = stack.Pop();
            ret.Add(cur.val);
            
            // Go right by one (if we can).
            root = cur.right;
        }
        
        
        return ret;
    }
}
