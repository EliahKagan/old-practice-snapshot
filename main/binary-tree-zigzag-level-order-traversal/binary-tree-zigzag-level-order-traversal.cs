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
    public IList<IList<int>> ZigzagLevelOrder(TreeNode root) {
        var ret = new List<IList<int>>();
        if (root == null) return ret;

        var deque = new LinkedList<TreeNode>();
        deque.AddLast(root);

        while (deque.Count != 0) {
            var row = new List<int>(); // left to right
            for (var width = deque.Count; width != 0; --width) {
                root = deque.First.Value;
                deque.RemoveFirst();

                row.Add(root.val);
                if (root.left != null) deque.AddLast(root.left);
                if (root.right != null) deque.AddLast(root.right);
            }
            ret.Add(row);

            if (deque.Count == 0) break;

            row = new List<int>(); // right to left
            for (var width = deque.Count; width != 0; --width) {
                root = deque.Last.Value;
                deque.RemoveLast();

                row.Add(root.val);
                if (root.right != null) deque.AddFirst(root.right);
                if (root.left != null) deque.AddFirst(root.left);
            }
            ret.Add(row);
        }

        return ret;
    }
}