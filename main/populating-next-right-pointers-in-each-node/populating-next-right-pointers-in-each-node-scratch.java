import java.util.ArrayList;
import java.util.List;

final class TreeLinkNode {
    int val;
    TreeLinkNode left, right, next;
    TreeLinkNode(int x) { val = x; }
}

final class Solution {
    public void connect(TreeLinkNode root) {
        if (root == null) return;

        List<TreeLinkNode> parents = new ArrayList<>();
        List<TreeLinkNode> children = new ArrayList<>();

        for (parents.add(root); !parents.isEmpty(); ) {
            // connect the parents
            final int last = parents.size() - 1;
            for (int i = 0; i != last; ++i)
                parents.get(i).next = parents.get(i + 1);
            parents.get(last).next = null;

            // discover the children
            for (final TreeLinkNode node : parents) {
                if (node.left != null) children.add(node.left);
                if (node.right != null) children.add(node.right);
            }

            // the children are the next iteration's parents
            final List<TreeLinkNode> tmp = parents;
            parents = children;
            children = tmp;
            children.clear();
        }
    }
}

@FunctionalInterface
interface IntegerQuadConsumer {
    void accept(Integer h, Integer i, Integer j, Integer k);
}

final class UnitTest {
    public static void main(final String[] args) {
        final TreeLinkNode[] nodes = new TreeLinkNode[10];
        for (int i = 0; i != nodes.length; ++i) nodes[i] = new TreeLinkNode(i);

        final IntegerQuadConsumer set = (cur, left, right, next) -> {
            if (left != null) nodes[cur].left = nodes[left];
            if (right != null) nodes[cur].right = nodes[right];
            if (next != null) nodes[cur].next = nodes[next];
        };

        set.accept(0, 1, 2, 3);
        set.accept(1, 3, 4, 8);
        set.accept(2, null, 5, 2);
        set.accept(3, null, null, 4);
        set.accept(4, 6, 7, 7);
        set.accept(5, 8, null, 9);
        set.accept(6, 9, null, 1);
        set.accept(7, null, null, null);
        set.accept(8, null, null, 6);

        new Solution().connect(nodes[0]);

        for (int i = 0; i != nodes.length; ++i) {
            Integer nextval = null;
            if (nodes[i].next != null) nextval = nodes[i].next.val;
            System.out.format("%d -> %s%n", nodes[i].val, nextval);
        }
    }

    private UnitTest() { throw new AssertionError(); }
}
