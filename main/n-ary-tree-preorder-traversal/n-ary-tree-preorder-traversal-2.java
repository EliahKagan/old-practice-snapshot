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
    public List<Integer> preorder(final Node root) {
        final List<Integer> acc = new ArrayList<>();
        if (root != null) dfs(acc, root);
        return acc;
    }

    private static void dfs(final List<Integer> acc, final Node root) {
        acc.add(root.val);
        for (final Node child : root.children) dfs(acc, child);
    }
}
