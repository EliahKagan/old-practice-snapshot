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
        if (root != null) dfs(acc, root);
        return acc;
    }

    private static void dfs(final List<Integer> acc, final Node node) {
        for (final Node child : node.children) dfs(acc, child);
        acc.add(node.val);
    }
}
