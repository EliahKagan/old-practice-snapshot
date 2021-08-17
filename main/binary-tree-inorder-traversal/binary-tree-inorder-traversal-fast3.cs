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

        bool GoLeft() {
            for (; root != null; root = root.left) stack.Push(root);
            return stack.Count != 0;
        }

        for (; GoLeft(); root = root.right) {
            root = stack.Pop();
            ret.Add(root.val);
        }

        return ret;
    }
}
