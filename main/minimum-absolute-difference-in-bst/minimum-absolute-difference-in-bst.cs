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
    public int GetMinimumDifference(TreeNode root)
        => Deltas(InOrder(root)).Min();

    private static IEnumerable<int> InOrder(TreeNode root) {
        if (root == null) yield break;

        foreach (var item in InOrder(root.left)) yield return item;
        yield return root.val;
        foreach (var item in InOrder(root.right)) yield return item;
    }

    private static IEnumerable<int> Deltas(IEnumerable<int> items) {
        using (var en = items.GetEnumerator()) {
            if (!en.MoveNext()) yield break;

            for (var prev = en.Current; en.MoveNext(); ) {
                var cur = en.Current;
                yield return cur - prev;
                prev = cur;
            }
        }
    }
}
