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
    public IList<int> PostorderTraversal(TreeNode root) {
        TreeNode last = null;
        var ret = new List<int>();
        var stack = new Stack<TreeNode>();
        
        while (root != null || stack.Count != 0) {
            // Go left as far as possible.
            for (; root != null; root = root.left) stack.Push(root);
            
            var cur = stack.Peek();
            
            if (cur.right != null && cur.right != last) {
                // We haven't gone right (and can). Go right.
                root = cur.right;
            } else {
                // We have already gone right (or can't). Retreat.
                ret.Add(cur.val);
                stack.Pop();
                last = cur;
            }
        }
        
        return ret;
    }
}
