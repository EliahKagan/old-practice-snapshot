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
    public IList<string> BinaryTreePaths(TreeNode root) {
        var ret = new List<string>();
        if (root == null) return ret;
        var path = new List<string>();

        void Dfs(TreeNode node) {
            path.Add(node.val.ToString());

            if (node.left != null || node.right != null) {
                if (node.left != null) Dfs(node.left);
                if (node.right != null) Dfs(node.right);
            }
            else ret.Add(string.Join("->", path));

            path.RemoveAt(path.Count - 1);
        }

        Dfs(root);
        return ret;
    }
}
