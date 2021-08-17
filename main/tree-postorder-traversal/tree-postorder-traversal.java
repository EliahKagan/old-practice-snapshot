/* you only have to complete the function given below.  
Node is defined as  

class Node {
    int data;
    Node left;
    Node right;
}

*/

    public static void postOrder(Node root) {
        Node last = null;
        final Deque<Node> stack = new ArrayDeque<>();
        
        while (root != null || !stack.isEmpty()) {
            // traverse left as far as possible
            for (; root != null; root = root.left) stack.push(root);
            
            final Node cur = stack.element();
            
            if (cur.right != null && cur.right != last) {
                // traverse right
                root = cur.right;
            } else {
                // retreat
                System.out.format("%d ", cur.data);
                last = cur;
                stack.pop();
            }
        }
    }
