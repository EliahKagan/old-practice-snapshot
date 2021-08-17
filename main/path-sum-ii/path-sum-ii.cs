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
    public IList<IList<int>> PathSum(TreeNode root, int sum) {
        var ret = new List<IList<int>>();
        if (root == null) return ret;
        var path = new List<int>();

        void Dfs(TreeNode node) {
            path.Add(node.val);
            sum -= node.val;

            if (node.left != null || node.right != null) {
                if (node.left != null) Dfs(node.left);
                if (node.right != null) Dfs(node.right);
            }
            else if (sum == 0) ret.Add(path.ToArray());

            sum += node.val;
            path.RemoveAt(path.Count - 1);
        }

        Dfs(root);
        return ret;
    }
}
