/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node class is defined as follows:
    class Node {
    int data;
    Node left;
    Node right;
     }
*/
    boolean checkBST(final Node root) {
        return rangeCheckBST(root, Long.MIN_VALUE, Long.MAX_VALUE);
    }

    private static boolean
    rangeCheckBST(final Node root, final long min, final long max) {
        return root == null || (min < root.data && root.data < max
                                && rangeCheckBST(root.left, min, root.data)
                                && rangeCheckBST(root.right, root.data, max));
    }
