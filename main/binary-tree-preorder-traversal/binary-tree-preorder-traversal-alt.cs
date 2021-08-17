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
    public IList<int> PreorderTraversal(TreeNode root) {
        var stack = new Stack<TreeNode>();
        var ret = new List<int>();
        
        while (root != null || stack.Count != 0) {
            for (; root != null; root = root.left) {
                ret.Add(root.val);
                stack.Push(root);
            }
            
            root = stack.Pop().right;
        }
        
        return ret;
    }
}
