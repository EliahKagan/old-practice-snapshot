/*
// Definition for a Node.
class Node {
    public int val;
    public List<Node> children;

    public Node() {}

    public Node(int _val,List<Node> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
    public List<Integer> postorder(final Node root) {
        final List<Integer> acc = new ArrayList<>();

        final Consumer<Node> dfs = new Consumer<Node>() {
            @Override public void accept(final Node node) {
                for (final Node child : node.children) accept(child);
                acc.add(node.val);
            }
        };

        if (root != null) dfs.accept(root);
        return acc;
    }
}
