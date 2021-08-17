	/*
    class Node 
    	int data;
    	Node left;
    	Node right;
	*/

    // This implementation assumes the tree is a BST that contains v1 and v2.
	public static Node lca(final Node root, final int v1, final int v2) {
        return v2 < v1 ? lcaImpl(root, v2, v1) : lcaImpl(root, v1, v2);
    }

    private static Node lcaImpl(Node root, final int low, final int high) {
        for (; ; ) {
            if (high < root.data)
                root = root.left;
            else if (root.data < low)
                root = root.right;
            else
                return root;
        }
    }
