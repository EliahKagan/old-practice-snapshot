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

    // The first tree pictured in the problem description is not a binary
    // search tree. This implementation does NOT assume the tree is a BST.
    private static Deque<Node> path(Node root, final int data)
    {
        final Deque<Node> stack = new ArrayDeque<>();
        Node last = null;
        
        while (root != null || !stack.isEmpty()) {
            // Go left as far as possible.
            for (; root != null; root = root.left) {
                stack.push(root);
                if (root.data == data) return stack;
            }
            
            final Node cur = stack.element();
            
            if (cur.right != null && cur.right != last) {
                // We can go right, but haven't yet.
                root = cur.right;
            } else {
                // We have already visited the right subtree (or it is empty).
                stack.pop();
                last = cur;
            }
        }
        
        return null;
    }
