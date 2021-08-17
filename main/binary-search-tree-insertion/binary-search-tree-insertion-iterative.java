 /* Node is defined as :
 class Node 
    int data;
    Node left;
    Node right;
    
    */

	public static Node insert(final Node root, final int data) {
        final Node leaf = new Node(data);
        if (root == null) return leaf;
        
        for (Node node = root; ; ) {
            if (data < node.data) {
                if (node.left == null) {
                    node.left = leaf;
                    break;
                }
                
                node = node.left;
            } else {
                if (node.right == null) {
                    node.right = leaf;
                    break;
                }
                
                node = node.right;
            }
        }
        
        return root;
    }
