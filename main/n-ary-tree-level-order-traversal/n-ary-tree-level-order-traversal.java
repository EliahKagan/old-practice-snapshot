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
    public List<List<Integer>> levelOrder(Node root) {
        final List<List<Integer>> ret = new ArrayList<>();
        if (root == null) return ret;

        final Queue<Node> queue = new ArrayDeque<>();
        queue.add(root);

        for (int level = 0; !queue.isEmpty(); ) {
            int width = queue.size();
            final List<Integer> row = new ArrayList<>(width);

            while (width-- != 0) {
                root = queue.remove();
                row.add(root.val);
                queue.addAll(root.children);
            }

            ret.add(row);
        }

        return ret;
    }
}
