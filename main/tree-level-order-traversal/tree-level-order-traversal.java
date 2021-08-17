	/* 
    
    class Node 
    	int data;
    	Node left;
    	Node right;
	*/
	public static void levelOrder(Node root) {
        if (root == null) return;
        
        final Deque<Node> queue = new ArrayDeque<>();
        queue.add(root);
        
        while (!queue.isEmpty()) {
            root = queue.remove();
            System.out.format("%d ", root.data);
            if (root.left != null) queue.add(root.left);
            if (root.right != null) queue.add(root.right);
        }
    }
    