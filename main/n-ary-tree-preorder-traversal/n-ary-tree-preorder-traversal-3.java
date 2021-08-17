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
        final List<Integer> ret = new ArrayList<>();
        if (root == null) return ret;

        final Deque<Iterator<Node>> stack = new ArrayDeque<>();
        stack.push(Arrays.asList(root).iterator());

        while (!stack.isEmpty()) {
            final Iterator<Node> it = stack.element();

            if (it.hasNext()) {
                final Node node = it.next();
                ret.add(node.val);
                stack.push(node.children.iterator());
            }
            else stack.pop();
        }

        return ret;
    }
}
