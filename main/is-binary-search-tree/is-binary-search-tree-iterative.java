/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node class is defined as follows:
    class Node {
    int data;
    Node left;
    Node right;
     }
*/
    boolean checkBST(Node root) {
        long acc = Long.MIN_VALUE;
        final Deque<Node> stack = new ArrayDeque<>();
        
        while (root != null || !stack.isEmpty()) {
            // go left as far as possible
            for (; root != null; root = root.left) stack.push(root);
            
            // visit the node
            final Node cur = stack.pop();
            if (cur.data <= acc) return false;
            acc = cur.data;
            
            // we will visit its right subtree next (if any)
            root = cur.right;
        }
        
        return true;
    }
