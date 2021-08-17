/* you only have to complete the function given below.  
Node is defined as  

class Node {
    int data;
    Node left;
    Node right;
}

*/

    public static void preOrder(Node root) {
        final Deque<Node> stack = new ArrayDeque<>();
        
        while (root != null || !stack.isEmpty()) {
            for (; root != null; root = root.left) {
                System.out.format("%d ", root.data);
                stack.push(root);
            }
            
            root = stack.pop().right;
        }
    }
