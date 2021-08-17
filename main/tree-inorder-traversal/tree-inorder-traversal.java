/* you only have to complete the function given below.  
Node is defined as  

class Node {
    int data;
    Node left;
    Node right;
}

*/

    public static void inOrder(Node root) {
        final Deque<Node> stack = new ArrayDeque<>();
        
        while (root != null || !stack.isEmpty()) {
            // traverse left as far as possible
            for (; root != null; root = root.left) stack.push(root);
            
            final Node cur = stack.pop();
            
            // the left subtree is fully explored, so process the data
            System.out.format("%d ", cur.data);
            
            // traverse right
            root = cur.right;
        }
    }
