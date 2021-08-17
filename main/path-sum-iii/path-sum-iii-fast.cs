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

        var history = new Dictionary<int, int> { { 0, 1 } }; // old subtotals
        var cur = 0; // current subtotal
        var count = 0; // the number of paths found that add to the desired sum

        void Dfs(TreeNode node) {
            cur += node.val;

            // Count prevs where cur - prev == total.
            if (history.TryGetValue(cur - sum, out var delta))
                count += delta;

            history.TryGetValue(cur, out var reps); // gives 0 if absent
            history[cur] = reps + 1;

            if (node.left != null) Dfs(node.left);
            if (node.right != null) Dfs(node.right);

            --history[cur];
            cur -= node.val;
        }

        Dfs(root);
        return count;
    }
}
