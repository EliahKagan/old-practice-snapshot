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
    public IList<TreeNode> FindDuplicateSubtrees(TreeNode root) {
        // (val, left id #, right id #) -> id #
        var ids = new Dictionary<ValueTuple<int, int, int>, int>();

        var nodes = new List<TreeNode>(); // id # -> a representative subroot

        var duped = new List<bool>(); // duped[i] is true iff id #i is duped

        int Identify(TreeNode node) {
            if (node == null) return -1;

            var key = (node.val, Identify(node.left), Identify(node.right));
            if (ids.TryGetValue(key, out var i)) {
                duped[i] = true; // was found, so this dupes it
                return i;
            } else {
                i = nodes.Count;
                ids[key] = i;
                nodes.Add(node);
                duped.Add(false); // not yet duped
                return i;
            }
        }

        Identify(root);

        return (from i in Enumerable.Range(0, nodes.Count)
                where duped[i]
                select nodes[i]).ToArray();
    }
}
