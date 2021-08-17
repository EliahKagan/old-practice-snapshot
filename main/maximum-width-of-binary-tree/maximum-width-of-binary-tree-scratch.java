import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

final class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;

    public TreeNode(int x) { val = x; }

    // Additional constructor, for debugging.
    TreeNode(final int val, final TreeNode left, final TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

final class IndexedNode {
    public final int index;
    public final TreeNode node;

    public IndexedNode(final int index, final TreeNode node) {
        this.index = index;
        this.node = node;
    }
}

class Solution {
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

final class UnitTest {
    public static void main(final String[] args) {
        final Stream<TreeNode> nodes = Stream.of(
                null,
                new TreeNode(10),
                new TreeNode(10, new TreeNode(20), new TreeNode(30)),
                new TreeNode(10, new TreeNode(20, new TreeNode(30), null),
                                 new TreeNode(40, null, new TreeNode(50))),
                new TreeNode(10, new TreeNode(20, null, new TreeNode(30)),
                                 new TreeNode(40, null, new TreeNode(50))));

        final Solution s = new Solution();

        nodes.forEachOrdered(node ->
                System.out.println(s.widthOfBinaryTree(node)));
    }
}
