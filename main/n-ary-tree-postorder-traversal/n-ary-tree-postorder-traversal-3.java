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

        final Deque<Frame> stack = new ArrayDeque<>();
        stack.push(new Frame(root));

        while (!stack.isEmpty()) {
            final Frame frame = stack.element();

            if (frame.it.hasNext()) {
                stack.push(new Frame(frame.it.next()));
            } else {
                ret.add(frame.val);
                stack.pop();
            }
        }

        return ret;
    }

    private static final class Frame {
        Frame(final Node node) {
            it = node.children.iterator();
            val = node.val;
        }

        final Iterator<Node> it;
        final int val;
    }
}
