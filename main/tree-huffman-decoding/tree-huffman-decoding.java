/*  
	class Node
		public  int frequency; // the frequency of this tree
    	public  char data;
    	public  Node left, right;
    
*/ 

	void decode(final String s, final Node root) {
        final StringBuilder sb = new StringBuilder();
        
        Node node = root;
        for (int i = 0; i != s.length(); ++i) {
            node = (s.charAt(i) == '0' ? node.left : node.right);
            
            if (node.left == null && node.right == null) {
                sb.append(node.data);
                node = root;
            }
        }
        
        System.out.println(sb);
    }
