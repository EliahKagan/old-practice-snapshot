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
    public int PathSum(TreeNode root, int sum) {
        if (root == null) return 0;
        var path = new List<int>();
        var count = 0;

        void DoCount(int partial) {
            if (partial == 0) ++count;

            foreach (var val in path) {
                partial += val;
                if (partial == 0) ++count;
            }
        }

        void Dfs(TreeNode node) {
            sum -= node.val;
            DoCount(sum);
            path.Add(node.val);

            if (node.left != null) Dfs(node.left);
            if (node.right != null) Dfs(node.right);

            path.RemoveAt(path.Count - 1);
            sum += node.val;
        }

        Dfs(root);
        return count;
    }
}
