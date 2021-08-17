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
    public bool IsSubtree(TreeNode s, TreeNode t) {
        const int null_id = -1, no_id = -2;
        var ids = new Dictionary<(int, int, int), int>();

        int CreateIds(TreeNode root) {
            if (root == null) return null_id;

            var key = (root.val, CreateIds(root.left), CreateIds(root.right));
            if (ids.TryGetValue(key, out var ret)) return ret;

            ret = ids.Count;
            ids.Add(key, ret);
            return ret;
        }

        int GetId(TreeNode root) {
            if (root == null) return null_id;

            var left_id = GetId(root.left);
            if (left_id == no_id) return no_id;

            var right_id = GetId(root.right);
            if (right_id == no_id) return no_id;

            return ids.TryGetValue((root.val, left_id, right_id), out var id)
                    ? id
                    : no_id;
        }

        CreateIds(s);
        return GetId(t) != no_id;
    }
}
