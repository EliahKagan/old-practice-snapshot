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
}
