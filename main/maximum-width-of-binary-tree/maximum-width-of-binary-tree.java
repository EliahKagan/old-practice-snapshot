/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
final class IndexedNode {
    public final int index;
    public final TreeNode node;

    public IndexedNode(final int index, final TreeNode node) {
        this.index = index;
        this.node = node;
    }
}

public class Solution {
    public int widthOfBinaryTree(TreeNode root) {
        int acc = 0;
        if (root == null) return acc;

        List<IndexedNode> this_row = new ArrayList<>();
        this_row.add(new IndexedNode(1, root));
        List<IndexedNode> next_row = new ArrayList<>();

        while (!this_row.isEmpty()) {
            acc = Math.max(acc, this_row.get(this_row.size() - 1).index
                                    - this_row.get(0).index + 1);

            for (final IndexedNode in : this_row) {
                if (in.node.left != null) {
                    next_row.add(new IndexedNode(in.index * 2,
                                                 in.node.left));
                }
                if (in.node.right != null) {
                    next_row.add(new IndexedNode(in.index * 2 + 1,
                                                 in.node.right));
                }
            }

            final List<IndexedNode> tmp = this_row;
            this_row = next_row;
            next_row = tmp;

            next_row.clear();
        }

        return acc;
    }
}
