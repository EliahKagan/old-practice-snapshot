/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    public TreeNode deleteNode(final TreeNode root, final int key) {
        final TreeNode meta = new TreeNode(Integer.MIN_VALUE);
        meta.right = root;

        final TreeLinkHandle pos = new TreeLinkHandle(meta, Side.RIGHT);
        descendTo(pos, key);

        if (pos.get() != null) {
            if (pos.get().left == null)
                pos.set(pos.get().right);
            else if (pos.get().right == null)
                pos.set(pos.get().left);
            else
                replace(pos, extractNextBelow(pos));
        }

        return meta.right;
    }

    private static void descendTo(final TreeLinkHandle pos, final int key) {
        while (pos.get() != null && pos.get().val != key)
            pos.go(key < pos.get().val ? Side.LEFT : Side.RIGHT);
    }

    private static void descendToMin(final TreeLinkHandle pos) {
        while (pos.get().left != null) pos.go(Side.LEFT);
    }

    private static TreeNode extractNextBelow(TreeLinkHandle pos) {
        pos = pos.copy();
        pos.go(Side.RIGHT);
        descendToMin(pos);

        final TreeNode ret = pos.get();
        pos.set(ret.right);
        return ret;
    }

    private static void replace(final TreeLinkHandle pos, final TreeNode node) {
        node.left = pos.get().left;
        node.right = pos.get().right;
        pos.set(node);
    }
}

/** Identifies which direction to traverse in a binary tree. */
enum Side { LEFT, RIGHT }

/** A re-seatable handle to use or change a child pointer in a binary tree. */
final class TreeLinkHandle {
    TreeLinkHandle(final TreeNode parent, final Side side) {
        _parent = parent;
        _side = side;
    }

    TreeNode get() {
        switch (_side) {
        case LEFT:
            return _parent.left;
        case RIGHT:
            return _parent.right;
        }

        throw new AssertionError("Internal error: can't read invalid side!");
    }

    void set(final TreeNode node) {
        switch (_side) {
        case LEFT:
            _parent.left = node;
            return;
        case RIGHT:
            _parent.right = node;
            return;
        }

        throw new AssertionError("Internal error: can't write invalid side!");
    }

    void go(final Side side) {
        _parent = get();
        _side = side;
    }

    TreeLinkHandle copy() {
        return new TreeLinkHandle(_parent, _side);
    }

    private TreeNode _parent;

    private Side _side;
}
