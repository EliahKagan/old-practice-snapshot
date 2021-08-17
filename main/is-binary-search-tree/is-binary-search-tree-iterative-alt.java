/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node class is defined as follows:
    class Node {
    int data;
    Node left;
    Node right;
     }
*/
    private enum Action { GO_LEFT, GO_RIGHT, RETREAT; }

    private static class Frame {
        Frame(final Node node) {
            this.node = node;
            this.action = Action.GO_LEFT;
        }
        
        final Node node;
        Action action;
    }

    boolean checkBST(final Node root) {
        if (root == null) return true;
        
        long acc = Long.MIN_VALUE;
        final Deque<Frame> stack = new ArrayDeque<>();
        stack.push(new Frame(root));
        
        while (!stack.isEmpty()) {
            final Frame frame = stack.element();
            
            switch (frame.action) {
            case GO_LEFT:
                frame.action = Action.GO_RIGHT;

                if (frame.node.left != null)
                    stack.push(new Frame(frame.node.left));

                break;

            case GO_RIGHT:
                frame.action = Action.RETREAT;

                if (frame.node.data <= acc) return false;
                acc = frame.node.data;

                if (frame.node.right != null)
                    stack.push(new Frame(frame.node.right));

                break;

            case RETREAT:
                stack.pop();
                break;
            }
        }
        
        return true;
    }
