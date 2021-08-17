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

        final Deque<Node> stack = new ArrayDeque<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            final Node node = stack.pop();
            ret.add(node.val);

            final List<Node> kids = node.children;
            final ListIterator<Node> it = kids.listIterator(kids.size());
            while (it.hasPrevious()) stack.push(it.previous());
        }

        return ret;
    }
}
