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
    public List<Integer> preorder(Node root) {
        final List<Integer> ret = new ArrayList<>();
        if (root == null) return ret;

        final Deque<Node> stack = new ArrayDeque<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            root = stack.pop();
            ret.add(root.val);

            final Deque<Node> children = new ArrayDeque<>(root.children);
            while (!children.isEmpty()) stack.push(children.removeLast());
        }

        return ret;
    }
}
