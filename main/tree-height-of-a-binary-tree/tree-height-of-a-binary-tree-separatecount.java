	/*
    class Node 
    	int data;
    	Node left;
    	Node right;
	*/
	public static int height(Node root) {
        int max = -1, cur = -1;
        
        Node last = root;
        final Deque<Node> stack = new ArrayDeque<>();
        
        while (root != null || !stack.isEmpty()) {
            // traverse left as far as possible
            for (; root != null; root = root.left) {
                stack.push(root);
                ++cur;
            }
            
            final Node node = stack.element();
            
            if (node.right != null && node.right != last) {
                // traverse right
                root = node.right;
            } else {
                // retreat
                if (max < cur) max = cur;
                --cur;
                last = node;
                stack.pop();
            }
        }
        
        return max;
    }
   