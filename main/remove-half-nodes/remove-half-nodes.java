/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*Complete the function below
Node is as follows:
class Node{
    int data;
    Node left,right;
    Node(int d){
        data=d;
        left=right=null;
    }
}
*/
class GfG {
    private static Node collapse(Node root)
    {
        while ((root.left == null) != (root.right == null))
            root = (root.left == null ? root.right : root.left);

        return root;
    }

    private static void collapseAllBelow(Node root)
    {
        if (root.left != null) {
            root.left = collapse(root.left);
            collapseAllBelow(root.left);
        }

        if (root.right != null) {
            root.right = collapse(root.right);
            collapseAllBelow(root.right);
        }
    }

    public Node removeHalfNodes(Node root)
    {
        final Node sentinel = new Node(0);
        sentinel.right = root;
        collapseAllBelow(sentinel);
        return sentinel.right;
    }
}
