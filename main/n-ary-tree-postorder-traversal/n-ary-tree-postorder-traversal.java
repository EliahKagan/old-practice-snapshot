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
        final List<Integer> ret = new ArrayList<>();
        if (root == null) return ret;

        final Deque<Node> stack = new ArrayDeque<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            final Node node = stack.pop();
            ret.add(node.val);
            for (final Node child : node.children) stack.push(child);
        }

        Collections.reverse(ret);
        return ret;
    }
}
