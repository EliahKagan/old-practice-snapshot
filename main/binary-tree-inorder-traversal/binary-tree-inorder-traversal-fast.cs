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

        for (; root != null; root = root.left)
            stack.Push(root);

        while (stack.Count != 0) {
            root = stack.Pop();
            ret.Add(root.val);

            for (root = root.right; root != null; root = root.left)
                stack.Push(root);
        }

        return ret;
    }
}
