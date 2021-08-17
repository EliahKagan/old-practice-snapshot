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
	public boolean isIsomorphic(final Node root1, final Node root2) {
	    if (root1 == null) return root2 == null;
	    if (root2 == null || root1.data != root2.data) return false;

	    return (isIsomorphic(root1.left, root2.left)
	            && isIsomorphic(root1.right, root2.right))
	        || (isIsomorphic(root1.left, root2.right)
	            && isIsomorphic(root1.right, root2.left));
	}
}
