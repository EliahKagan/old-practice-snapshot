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
        Frame(final Node node, final long min, final long max) {
            this.node = node;
            this.min = min;
            this.max = max;
            this.action = Action.GO_LEFT;
        }
        
        final Node node;
        final long min, max;
        Action action;
    }

    boolean checkBST(final Node root) {
        if (root == null) return true;
        
        final Deque<Frame> stack = new ArrayDeque<>();
        stack.push(new Frame(root, Long.MIN_VALUE, Long.MAX_VALUE));
        
        while (!stack.isEmpty()) {
            final Frame frame = stack.element();
            final long data = frame.node.data;
            
            switch (frame.action) {
            case GO_LEFT:
                frame.action = Action.GO_RIGHT;
                
                if (!(frame.min < frame.node.data
                      && frame.node.data < frame.max))
                    return false;
                
                if (frame.node.left != null) {
                    stack.push(new Frame(frame.node.left,
                                         frame.min, frame.node.data));
                }
                
                break;
                
            case GO_RIGHT:
                frame.action = Action.RETREAT;
                
                if (frame.node.right != null) {
                    stack.push(new Frame(frame.node.right,
                                         frame.node.data, frame.max));
                }
                
                break;
                
            case RETREAT:
                stack.pop();
                break;
            }
        }
        
        return true;
    }
