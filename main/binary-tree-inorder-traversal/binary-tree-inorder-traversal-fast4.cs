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
        IEnumerable<int> Dfs(TreeNode node) {
            for (var stack = new Stack<TreeNode>();
                    node != null || stack.Count != 0; node = node.right) {
                // traverse left
                for (; node != null; node = node.left) stack.Push(node);

                // visit the subroot
                node = stack.Pop();
                yield return node.val;
            }
        }

        return Dfs(root).ToList();
    }
}
