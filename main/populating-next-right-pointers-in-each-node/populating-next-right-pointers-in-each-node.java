public class TreeLinkNode {
    int val;
    TreeLinkNode left, right, next;
    TreeLinkNode(int x) { val = x; }
}

public class Solution {
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
