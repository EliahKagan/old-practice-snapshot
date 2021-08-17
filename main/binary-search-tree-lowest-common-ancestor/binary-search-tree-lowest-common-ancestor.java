	/*
    class Node 
    	int data;
    	Node left;
    	Node right;
	*/

	public static Node lca(Node root, int v1, int v2) {
        // Find the root-to-node paths for the nodes with v1 and v2 data.
      	final Deque<Node> p1 = path(root, v1), p2 = path(root, v2);
        if (p1 == null) throw new IllegalArgumentException("v1 not found");
        if (p2 == null) throw new IllegalArgumentException("v2 not found");
        
        // Trim a suffix from the longer path, so they are the same length.
        while (p1.size() > p2.size()) p1.pop();
        while (p2.size() > p1.size()) p2.pop();
        
        // Trim suffixes from both paths until the convergence point is found.
        while (p1.element() != p2.element()) {
            p1.pop();
            p2.pop();
        }
        
        return p1.element();
    }

    // This implementation assumes the tree is a binary search tree.
    private static Deque<Node> path(Node root, final int data)
    {
        final Deque<Node> stack = new ArrayDeque<>();
        
        while (root != null) {
            stack.push(root);
            if (data == root.data) return stack;
            root = (data < root.data ? root.left : root.right);
        }
        
        return null;
    }
