public class Solution {
    public TreeNode DeleteNode(TreeNode root, int key)
    {
        ref var pos = ref Find(ref root, key);

        if (pos != null) {
            if (pos.left == null)
                pos = pos.right;
            else if (pos.right == null)
                pos = pos.left;
            else
                Replace(ref pos, ExtractMin(ref pos.right));
        }

        return root;
    }

    private static ref TreeNode Find(ref TreeNode root, int key)
    {
        if (root == null || root.val == key) return ref root;

        for (var parent = root; ; ) {
            ref var child = ref (key < parent.val ? ref parent.left
                                                  : ref parent.right);

            if (child == null || child.val == key) return ref child;

            parent = child;
        }
    }

    private static ref TreeNode FindMin(ref TreeNode root)
    {
        if (root.left == null) return ref root;

        var parent = root;
        while (parent.left.left != null) parent = parent.left;
        return ref parent.left;
    }

    private static TreeNode ExtractMin(ref TreeNode root)
    {
        ref var pos = ref FindMin(ref root);
        var ret = pos;
        pos = ret.right;
        ret.right = null; // makes debugging easier
        return ret;
    }

    private static void Replace(ref TreeNode oldNode, TreeNode newNode)
    {
        newNode.left = oldNode.left;
        newNode.right = oldNode.right;
        oldNode.left = oldNode.right = null; // makes debugging easier
        oldNode = newNode;
    }
}
