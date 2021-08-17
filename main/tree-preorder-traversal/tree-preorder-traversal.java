/* you only have to complete the function given below.  
Node is defined as  

class Node {
    int data;
    Node left;
    Node right;
}

*/

    public static void preOrder(final Node root) {
        final Deque<Node> stack = new ArrayDeque<>();
        if (root != null) stack.push(root);
        
        while (!stack.isEmpty()) {
            final Node node = stack.pop();
            System.out.format("%d ", node.data);
            if (node.right != null) stack.push(node.right);
            if (node.left != null) stack.push(node.left);
        }
    }
