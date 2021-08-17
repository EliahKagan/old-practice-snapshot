import java.util.Deque;

public class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}

class Solution {
    public List<Integer> rightSideView(TreeNode root) {
        final List<Integer> ret = new ArrayList<>();
        if (root == null) return ret;

        final Deque<TreeNode> q = new ArrayDeque<>();
        for (q.add(root); !q.isEmpty(); ) {
            ret.add(q.peekLast().val);
            for (int width = q.size(); width != 0; --width) {
                root = q.pop();
                if (root.left != null) q.add(root.left);
                if (root.right != null) q.add(root.right);
            }
        }

        return ret;
    }
}
